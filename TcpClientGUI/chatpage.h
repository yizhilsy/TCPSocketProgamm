#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QDialog>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <thread>
#include "selectuser.h"
#include <QThread>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

namespace Ui {
class chatpage;
}

class chatpage : public QDialog
{
    Q_OBJECT

signals:
    void outputMessage(const QString& message); //信号

public slots:
    void handleFunOutput(const QString& message);   //槽函数

public:
    explicit chatpage(SOCKET clientSocket,SOCKET clientSocket_oc,int* p,QWidget *parent = nullptr);
    ~chatpage();

public slots:
    void onMessageReceived(const QString& message);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    //chatpage页面关闭响应槽函数
    //void closeEvent(QCloseEvent* event);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::chatpage *ui;
    SOCKET clientSocket;SOCKET clientSocket_oc;
    int* p;
};

#endif // CHATPAGE_H
