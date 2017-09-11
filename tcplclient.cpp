#include "tcpclient.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
#include<signal.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<iostream>
#define MAXDATASIZE 100


tcpClient::tcpClient(string host,string port)
{
    hostname = host;
    PORT = port;

}

void* tcpClient::get_in_addr(struct sockaddr *sa)
{
if(sa->sa_family == AF_INET)
    return &(((struct sockaddr_in*)sa)->sin_addr);
return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int tcpClient::initializeTcpClient()
{
    struct addrinfo hints, *servinfo ,*p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if((rv = getaddrinfo(hostname.c_str(), PORT.c_str(), &hints, &servinfo)) != 0)
   {
       fprintf(stderr, "getaddrinfo:%s\n",gai_strerror(rv));
       return 1;
   }

     for(p = servinfo; p != NULL; p = p->ai_next)
     {
        if((clientSockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
       {
       perror("client:socket");
       continue;
       }

        if(connect(clientSockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(clientSockfd);
            perror("client:socket");
            continue;
        }

        break;

        }

    if(p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        return 1;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),s ,sizeof(s));
    printf("client: connecting to:%s\n",s);

    freeaddrinfo(servinfo);
    return 0;
}
string tcpClient::recieveMessage()
{
    int  numbytes;
    char buf[MAXDATASIZE];

    if((numbytes = recv(clientSockfd, buf, MAXDATASIZE -1, 0)) == -1)
    {
        perror("recv");
        exit(1);
    }
    if(numbytes == 0)
        throw int(5);
    buf[numbytes] = '\0';

    std::cout<<"client: received:"<<buf<<std::endl;
    return string(buf);
}


void tcpClient::sendMessage(string text)
{

    if(send(clientSockfd, text.c_str(), sizeof(text.c_str()), 0) == -1)
        perror("\nerror sending message:no socket");

}


tcpClient::~tcpClient()
{
    close(clientSockfd);
}




