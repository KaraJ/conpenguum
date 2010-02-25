#ifndef TCPCLIENT_H
#define TCPCLIENT_H

//System Includes
#include <netdb.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <queue>

//User Includes
#include "comm/globals.h"
#include "comm/data/servermessage.h"
#include "Logger.h"
#include "comm/tcpconnection.h"

class TCPClient
{
public:
    bool Connect(const std::string& ip);
    void StartRdThread(std::queue<ServerMessage> *msgBuff, );
    ServerMessage Login(std::string playerName);
    bool IsConnected();
    void Logout();

private:
    bool connected;
    int  tcpSocket;
    std::queue<ServerMessage> *msgBuff_;
};

#endif // TCPCLIENT_H
