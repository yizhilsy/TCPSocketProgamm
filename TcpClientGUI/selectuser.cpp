#include "selectuser.h"
#include "ui_selectuser.h"
#include <QMessageBox>
#include "chatpage.h"

selectUser::selectUser(SOCKET clientSocket,SOCKET clientSocket_oc,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectUser)
{
    this->clientSocket=clientSocket;this->clientSocket_oc=clientSocket_oc;
    ui->setupUi(this);
}

selectUser::~selectUser()
{
    delete ui;
}
void selectUser::on_pushButton_clicked()
{
    QString qqtarget=ui->lineEdit->text();
    string target = qqtarget.toStdString();
    send(this->clientSocket,target.c_str(),target.size(),0);
    char isconnect[128]={0};
    recv(this->clientSocket,isconnect,sizeof(isconnect),0);
    cout<<isconnect<<endl;
    string connectans(isconnect);
    QMessageBox::information(this,"tips",isconnect);
    this->close();
}

