#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <cstring>
#include <netinet/in.h>
#include "comm/socketwrapper.h"
#include "comm/data/globals.h"

class UDPServer
{
public:
    UDPServer();
    void sendMessage(struct sockaddr* to, const void* data, size_t dataLen);
private:
    int sockfd_;
};

#endif
