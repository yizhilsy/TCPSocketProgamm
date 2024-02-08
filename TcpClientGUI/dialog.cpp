#include "dialog.h"
#include "./ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(SOCKET clientSocket,SOCKET clientSocket_oc,int *p,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    this->clientSocket=clientSocket;this->clientSocket_oc=clientSocket_oc;this->p=p;
    ui->setupUi(this);
    //chat页面关闭事件与槽函数绑定
    //connect(this,SIGNAL(closeEvent(QCloseEvent*)),this,SLOT(closeEvent(QCloseEvent*)));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QString qqusername=ui->txtusername->text();QString qqpassword=ui->txtpassword->text();
    string username=qqusername.toStdString();string password=qqpassword.toStdString();
    cout<<"-->"<<username<<","<<password<<endl;

    //服务器验证登录状态
    send(clientSocket, (username + "," + password).c_str(), (username + "," + password).size(), 0);
    char response[128] = { 0 };
    recv(clientSocket, response, sizeof(response), 0);
    char connectstatus = response[0];
    cout << response << endl;
    cout<<"-->connectstatus: "<<connectstatus<<endl;
    if(connectstatus=='W'){ //root用户yizhilsy
        QMessageBox::information(this,"tips","login success");
        this->close();
        chatpage* chapic=new chatpage(this->clientSocket,this->clientSocket_oc,p);
        chapic->show();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Wrong Username or Password, please try again");
        msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        msgBox.exec();
    }
}

////dialog页面关闭响应槽函数
//void Dialog::closeEvent(QCloseEvent* event){
//    //向服务器发送下线请求
//    string quser="chatflymessage";string qpass="quit";
//    quser=quser+','+qpass;
//    cout<<quser<<endl;
//    send(this->clientSocket,quser.c_str(),quser.size(),0);
//    //关闭套接字
//    closesocket(clientSocket);
//    closesocket(clientSocket_oc);
//    WSACleanup();
//    cout<<"main page exit chat flymessage"<<endl;
//    QDialog::closeEvent(event);
//}


void Dialog::on_pushButton_2_clicked()
{
    //向服务器发送程序下线请求
    string quser="chatflymessage";string qpass="quit";
    quser=quser+','+qpass;
    send(this->clientSocket,quser.c_str(),quser.size(),0);
    //关闭套接字
    closesocket(clientSocket);
    closesocket(clientSocket_oc);
    WSACleanup();
    cout<<"main page exit chat flymessage"<<endl;
    //关闭接收消息进程
    *(this->p)=0;
    this->close();
}

