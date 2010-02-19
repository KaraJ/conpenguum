#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <cstring>
#include <netinet/in.h>

#include "comm/socketwrapper.h"
#include "comm/globals.h"

class UDPServer
{
public:
    UDPServer();
    void sendMessage(struct sockaddr* to, const void* data, size_t dataLen);
    void EchoMessage();
private:
    int sockfd_; // the socket file descriptor
};

#endif
