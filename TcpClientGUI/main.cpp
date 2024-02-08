#include "dialog.h"
#include <QApplication>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <QString>
#include "recvwindow.h"
using namespace std;
#pragma comment(lib,"ws2_32.lib")

vector<string> rv;
//独立线程不断接受来自其他用户的信息
int IsContinue = true;
void ReceiveMessage(SOCKET clientSocket_oc,RecvWindow* rec) {
    while (IsContinue) {
        char receivebuffer[1024] = {0};
        recv(clientSocket_oc, receivebuffer, sizeof(receivebuffer), 0);
        string herestr(receivebuffer);
        rv.push_back(herestr);
        herestr+='\n';
        QString ans=QString::fromStdString(herestr);
        rec->addmess(ans);
    }
    cout << "用户下线，接受其他用户信息的线程销毁" << endl;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //SOCKET网络初始化
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //此SOCKET只接受服务端自有信息
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    //此SOCKET只接受其他客户端发送的信息
    SOCKET clientSocket_oc = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    ::connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    sockaddr_in serverAddr2;
    serverAddr2.sin_family = AF_INET;
    serverAddr2.sin_port = htons(12346);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr2.sin_addr);
    ::connect(clientSocket_oc, (struct sockaddr*)&serverAddr2, sizeof(serverAddr2));

    int* p=&IsContinue;
    Dialog w(clientSocket,clientSocket_oc,p);
    w.show();

    RecvWindow recwin(clientSocket_oc,&rv);
    recwin.show();

    //创建线程
    thread(ReceiveMessage, clientSocket_oc,&recwin).detach();





    //关闭独立线程
    cout<<"111"<<endl;
    return a.exec();
}
