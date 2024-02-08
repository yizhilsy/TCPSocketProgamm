#include "chatpage.h"
#include "qobjectdefs.h"
#include "ui_chatpage.h"
#include "dialog.h"

chatpage::chatpage(SOCKET clientSocket,SOCKET clientSocket_oc,int* p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatpage)
{
    ui->setupUi(this);
    this->clientSocket=clientSocket;this->clientSocket_oc=clientSocket_oc;this->p=p;
    //chat页面关闭事件与槽函数绑定
    //connect(this,SIGNAL(chatpage::closeEvent(QCloseEvent*)),this,SLOT(chatpage::closeEvent(QCloseEvent*)));
    //connect(this,SIGNAL(outputMessage(QString)),ui->textBrowser,SLOT(append(QString)));
}

chatpage::~chatpage()
{
    delete ui;
}

void chatpage::on_pushButton_2_clicked()    //退出当前用户的登录
{
    Dialog* fatherpage = new Dialog(clientSocket,clientSocket_oc,p);
    string strmes="exitmain";
    send(clientSocket,strmes.c_str(),strmes.size(),0);
    char byeword[128]={0};
    recv(this->clientSocket,byeword,sizeof(byeword),0);
    QMessageBox::information(this,"tips",byeword);
    this->close();
    fatherpage->show();
}


void chatpage::on_pushButton_clicked()  //发送函数
{
    //发送讯息
    QString textmessage="You: ";
    textmessage+=ui->textEdit->toPlainText();
    textmessage+='\n';

    QString temp=ui->textEdit->toPlainText();
    ui->textBrowser->insertPlainText(textmessage);
    ui->textEdit->clear();
    string sendinfo=temp.toStdString();
    send(this->clientSocket,sendinfo.c_str(),sendinfo.size(),0);
}

//void chatpage::closeEvent(QCloseEvent* event){
//    //执行返回主登录界面
//    Dialog* fatherpage = new Dialog(clientSocket,clientSocket_oc);
//    fatherpage->show();
//    this->close();
//    //QDialog::closeEvent(event);
//}

void chatpage::on_pushButton_3_clicked()
{
    //查询更新目前在线用户
    string query="que";
    send(this->clientSocket,query.c_str(),query.size(),0);
    char onlinueuserret[1024] = { 0 };
    recv(clientSocket, onlinueuserret, sizeof(onlinueuserret), 0);
    ui->textBrowser_2->clear();
    ui->textBrowser_2->insertPlainText(onlinueuserret);
}

void chatpage::onMessageReceived(const QString& message){
    string target=message.toStdString();
    send(this->clientSocket,target.c_str(),target.size(),0);
}


void chatpage::on_pushButton_4_clicked()
{
    string strchat="chat";
    send(this->clientSocket,strchat.c_str(),strchat.size(),0);
    //调用新窗口
    selectUser* sc = new selectUser(this->clientSocket,this->clientSocket_oc);
    sc->show();
}

void chatpage::on_pushButton_5_clicked()
{
    string shiftchatstr="exityes";
    send(this->clientSocket,shiftchatstr.c_str(),shiftchatstr.size(),0);
    char byeword[64] = { 0 };
    recv(clientSocket, byeword, sizeof(byeword), 0);
    QMessageBox::information(this,"tips",byeword);
}

void chatpage::handleFunOutput(const QString& message){
    //及时添加发送的数据
    ui->textBrowser->insertPlainText(message);
}



