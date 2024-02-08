#include "recvwindow.h"
#include "ui_recvwindow.h"

RecvWindow::RecvWindow(SOCKET clientSocket_oc,vector<string> *rv,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecvWindow)
{
    ui->setupUi(this);
    this->clientSocket_oc=clientSocket_oc;this->rv=rv;
}

RecvWindow::~RecvWindow()
{
    delete ui;
}
void RecvWindow::freshmessage(){
    int ori=0;
    while(true){
        if(rv->size()>ori){
            ori=rv->size();
            string recs=rv->back();
            QString anothers=QString::fromStdString(recs);
            ui->textBrowser->insertPlainText(anothers);
        }
    }
}

void RecvWindow::addmess(QString qs){
    ui->textBrowser->insertPlainText(qs);
}
