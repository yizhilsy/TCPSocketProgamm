#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include "chatpage.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <thread>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(SOCKET clientSocket,SOCKET clientSocket_oc,int *p,QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    //dialog页面关闭响应槽函数
    //void closeEvent(QCloseEvent* event);

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    SOCKET clientSocket;SOCKET clientSocket_oc;
    int* p;
};
#endif // DIALOG_H
