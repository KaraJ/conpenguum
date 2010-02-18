#ifndef TCPCLIENT_H
#define TCPCLIENT_H

//This class to hold application specific logic for the TCP connection client

#include <string>
#include "comm/data/servermessage.h"

class TCPClient
{
public:
    TCPClient();
    ~TCPClient();
    int Login(std::string ip, int port);
    bool IsConnected();
    bool Logout();

private:
    bool connected;
};

#endif // TCPCLIENT_H
