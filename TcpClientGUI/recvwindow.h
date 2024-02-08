#ifndef RECVWINDOW_H
#define RECVWINDOW_H
#include <QDialog>
#include <QString>
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
class RecvWindow;
}

class RecvWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RecvWindow(SOCKET clientSocket_oc,vector<string> *rv,QWidget *parent = nullptr);
    ~RecvWindow();
    void freshmessage();
    void addmess(QString qs);

private:
    Ui::RecvWindow *ui;
    SOCKET clientSocket_oc;
    vector<string> *rv;
};

#endif // RECVWINDOW_H
