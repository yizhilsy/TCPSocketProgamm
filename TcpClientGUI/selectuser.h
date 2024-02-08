#ifndef SELECTUSER_H
#define SELECTUSER_H

#include <QDialog>
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

namespace Ui {
class selectUser;
}

class selectUser : public QDialog
{
    Q_OBJECT

public:
    explicit selectUser(SOCKET clientSocket,SOCKET clientSocket_oc,QWidget *parent = nullptr);
    ~selectUser();

signals:
    void messageSent(const QString& message);

private slots:


    void on_pushButton_clicked();

private:
    Ui::selectUser *ui;
    SOCKET clientSocket;SOCKET clientSocket_oc;
};

#endif // SELECTUSER_H
