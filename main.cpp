#include "mainwindow.h"
#include <QApplication>
#include"viewWidget.h"
#include"network.h"
#include<iostream>
#include<thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    network *n= new network("127.0.0.1","9034");
    viewWidget *w = new viewWidget;
    QObject::connect(n,SIGNAL(newMessageRecieved(QString)),w,SLOT(otherMessageRecieved(QString)));
    QObject::connect(w,SIGNAL(newMessageToBeSent(QString)),n,SLOT(messageSendingProcedure(QString)));

    n->startReceivingMessage();
    w->show();

    return a.exec();
}
