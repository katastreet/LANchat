#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include<string>
using std::string;

class QString;


class tcpClient
{
public:
    tcpClient(string host="\0",string port="\0");
    int initializeTcpClient();
    string recieveMessage();
    void sendMessage(string);
    ~tcpClient();
private:
    string hostname;
    string PORT;
    void *get_in_addr(struct sockaddr *sa);
    int clientSockfd;

};

#endif // TCPCLIENT_H
