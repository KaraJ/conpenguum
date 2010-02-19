#ifndef TCPCLIENT_H
#define TCPCLIENT_H

//System Includes
#include <netdb.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>

//User Includes
#include "comm/globals.h"
#include "comm/data/servermessage.h"
#include "Logger.h"
#include "comm/tcpconnection.h"

class TCPClient
{
public:
    TCPClient();
    ~TCPClient();
    void Connect(std::string& ip);
    int Login(std::string playerName);
    bool IsConnected();
    bool Logout();

private:
    bool connected;
    int  tcpSocket;
};

#endif // TCPCLIENT_H
