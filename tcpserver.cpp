#include <iostream>
#include <string>
#include <vector>;
#include <WinSock2.h>
#include <thread>
using namespace std;
struct User {
    string username;string password;
    SOCKET socket;SOCKET socket_oc;
};
struct RegUser {
    string username;
    string password;
};
vector<User> onlineusers;
vector<RegUser> registedusers;

void init();
void NewRegUser(string& username,string& password);
void AddUser(string username, string password, SOCKET socket,SOCKET socket_oc);  //添加在线用户
bool Authenticate(string username, string password);
void removeUser(string username, string password, SOCKET socket);   //强制下线某些在线用户
void questiononlinueuser(string& ans);
int isexist(string& s);
void questiononlinueuser(string& ans) {
    for (int i = 0; i < onlineusers.size(); i++) {
        ans += onlineusers[i].username; ans += ", "; ans += onlineusers[i].password;
        ans += '\n';
    }
}
int isexist(string& s) {
    for (int i = 0; i < onlineusers.size(); i++) {
        if (onlineusers[i].username == s) {
            return i;
        }
    }
    return -1;//没有找到当前在线的用户
}

//服务端线程
void clientHandler(SOCKET clientSocket,SOCKET clientSocket_oc);

int main() {
    cout << "********************Server*********************" << endl;
    init();
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // 创建套接字
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    SOCKET send2otherclient = socket(AF_INET, SOCK_STREAM, 0);


    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);//第一个端口
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    sockaddr_in serverAddr2;
    serverAddr2.sin_family = AF_INET;
    serverAddr2.sin_port = htons(12346); // 第二个端口
    serverAddr2.sin_addr.s_addr = htonl(INADDR_ANY);

    // 绑定套接字serverSocket
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // 绑定套接字send2otherclient
    bind(send2otherclient, (struct sockaddr*)&serverAddr2, sizeof(serverAddr2));

    // 两个套接字都开始监听连接
    listen(serverSocket, SOMAXCONN);
    listen(send2otherclient, SOMAXCONN);

    cout << "Server1 is listening on port 8080..." << endl;
    cout << "Server2 is listening on port 12346..." << endl;

    while (true) {
        // 接受客户机连接
        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        SOCKET clientSocket_oc = accept(send2otherclient, (struct sockaddr*)&clientAddr, &clientAddrSize);
        thread(clientHandler, clientSocket,clientSocket_oc).detach();
    }

    // 关闭套接字
    closesocket(serverSocket);
    closesocket(send2otherclient);
    WSACleanup();

    return 0;
}
void clientHandler(SOCKET clientSocket,SOCKET clientSocket_oc) {
    //循环登录-->身份核验
    while (true) {
        // 从客户端接收消息
        char buffer[512] = { 0 };
        recv(clientSocket, buffer, sizeof(buffer), 0);
        cout << "server recv: " << buffer << endl;
        string loginInfo(buffer);
        string username = loginInfo.substr(0, loginInfo.find(","));
        string password = loginInfo.substr(loginInfo.find(",") + 1, loginInfo.size());
        if (username == "chatflymessage" && password == "quit") {
            cout << "某个用户登出" << endl;
            //终止循环登录,终止client1以及client2,该线程销毁
            closesocket(clientSocket); closesocket(clientSocket_oc);
            return;break;
        }
        else {
            cout << "现在接收到了账号：" << username << "," << password << endl;
        }
        //身份核验
        cout << Authenticate(username, password) << endl;
        if (Authenticate(username, password)) {
            string newstr = "Welcome! User: "+username;
            send(clientSocket, newstr.c_str(), newstr.size(), 0);
            cout << newstr << endl;
            //登录成功，添加在线用户数据
            AddUser(username, password, clientSocket, clientSocket_oc);
            while (true) {  //与登录的账号进行交互
                //交互操作符nextstep
                char control[128] = { 0 };
                recv(clientSocket, control, sizeof(control), 0);
                string nextstep(control);
                cout << nextstep << endl;
                if (nextstep == "que") {
                    string ans;
                    questiononlinueuser(ans);
                    send(clientSocket, ans.c_str(), ans.size(), 0);
                }
                else if (nextstep == "exitmain") {
                    //客户端终止连接
                    string byemessage = "Bye, User " + username;
                    send(clientSocket, byemessage.c_str(), byemessage.size(), 0);
                    //移除在线数据
                    removeUser(username, password, clientSocket);
                    cout << "User " << username << " logout..." << endl;
                    break;
                }
                else if (nextstep == "chat") {
                    //接收申请聊天的对象并且验证是否匹配
                    char recvtarget[128] = { 0 };
                    recv(clientSocket, recvtarget, sizeof(recvtarget), 0);
                    string wantuser(recvtarget);
                    cout << username << " want chat with " << wantuser << endl;
                    int pos = isexist(wantuser);
                    if (pos != -1) {
                        cout << "Connect Success!" << endl;
                        //发送连接情况
                        string issuccess = "connect success";
                        send(clientSocket, issuccess.c_str(), issuccess.size(), 0);
                        char say[1024] = { 0 };
                        while (true) {  //进行循环通信
                            memset(say, 0, sizeof(say));
                            recv(clientSocket, say, sizeof(say), 0);
                            string recmessage(say);
                            if (recmessage == "exityes") {  //用户结束其与wantuser的对话
                                //服务器发送结束请求
                                cout << username << " done the chat with " << wantuser << endl;
                                string byemessage = "has disconnected the chat with " + wantuser;
                                send(clientSocket, byemessage.c_str(), byemessage.size(), 0);
                                break;
                            }
                            else {
                                //实施正常通信
                                cout << "User " << username << " Send: " << recmessage << " to " << wantuser << endl;
                                //发送给目标B用户,通过socket_oc套接字
                                string newrecmessage = username + ": " + recmessage;
                                send(onlineusers[pos].socket_oc, newrecmessage.c_str(), newrecmessage.size(), 0);
                            }
                        }
                    }
                    else {
                        string issuccess = "connect fail! no such user " + wantuser + "!";
                        cout << username << " " << issuccess << endl;

                        send(clientSocket, issuccess.c_str(), issuccess.size(), 0);
                    }

                }
            }
        }
        else {
            cout << username << "的账号或密码有误!" << endl;
            //发送消息令client用户端口程序重新登录
            send(clientSocket, "Authentication failed.Please login again.", 50, 0);
        }
    }
    
    
}

void init() {   //初始化根用户
    RegUser user1; user1.username = "yizhilsy"; user1.password = "Lsy200304144815";
    RegUser user2; user2.username = "Greg"; user2.password = "0625";    
    RegUser user3; user3.username = "Roy064"; user3.password = "cheemsdogteam";
    registedusers.push_back(user1); registedusers.push_back(user2); registedusers.push_back(user3);
}
void AddUser(string username, string password, SOCKET socket,SOCKET socket_oc) {
    User user; user.username = username; user.password = password;
    user.socket = socket; user.socket_oc = socket_oc;
    onlineusers.push_back(user);
}
bool Authenticate(string username, string password) {
    for (int i = 0; i < registedusers.size(); i++) {
        if (registedusers[i].username == username && registedusers[i].password == password) {
            return true;    //身份核验成功
        }
    }
    return false;   //身份非法
}
void removeUser(string username, string password, SOCKET socket) {  //强制下线某些在线用户
    for (int i = 0; i < onlineusers.size(); i++) {
        if (onlineusers[i].username == username && onlineusers[i].password == password && onlineusers[i].socket == socket) {
            vector<User>::iterator it = onlineusers.begin() + i;
            onlineusers.erase(it);  //强制下线某些在线用户
            break;
        }
    }
}
void NewRegUser(string& username, string& password) {
    RegUser newclient; newclient.username = username; newclient.password = password;
    registedusers.push_back(newclient);
}