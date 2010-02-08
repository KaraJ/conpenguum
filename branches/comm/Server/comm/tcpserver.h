#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "message.h"
#include "servermessage.h"
#include "chatmessage.h"
#include <pthread.h>
#include <errno.h>
#include <queue>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <QTime>


#define MAXQUERIES 50

class TCPServer
{

private:
    static int connections;
    int port;
    int maxClients;
    int timeOut;
    std::queue<ServerMessage> sMsgList;
    std::queue<ChatMessage> cMsgList;
    QTime start;

public:
    TCPServer(int, int);
    TCPServer();
    void Run();
    bool HasMessages();
    void SendMessage(Message);
    Message GetMessage();

private:
    void *ClientConnectThread(void *);

};

#endif // TCPSERVER_H
