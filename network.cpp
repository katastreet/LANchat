#include<QString>
#include"network.h"
#include"tcpclient.h"
#include<thread>
#include<iostream>
#include<chrono>



network::network(QString host,QString p,QObject *parent) : QObject(parent)
{
    hostname=host;
    port=p;

}
void network::messageRecievingProcedure()
{
    n=new tcpClient(hostname.toStdString(),port.toStdString());
    while(1)
    {
    try{
    if(n->initializeTcpClient() != 0)
        throw int(1);

    while(1)
    {
            emit newMessageRecieved( QString::fromUtf8(n->recieveMessage().c_str()));//std string to qstring
    }
    }
    catch(int)
    {
        std::cerr<<"coudln't create client socket";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    }

}
void network::messageSendingProcedure(const QString& text)
{
    n->sendMessage(text.toStdString());

}

void network::startReceivingMessage()
{
    std::thread t(&network::messageRecievingProcedure,this);
    std::cout<<"thread created"<<std::endl;
    t.detach();
}





