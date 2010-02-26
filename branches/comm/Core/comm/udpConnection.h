#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <cstring>
#include <netinet/in.h>

#include "socketwrapper.h"
#include "globals.h"
#include "data/updateobject.h"
#include "crc.h"

class UDPConnection
{
public:
    UDPConnection();
    ~UDPConnection();
    void sendMessage(struct sockaddr* to, const void* data, size_t dataLen);
    ssize_t recvMessage(BYTE** buffer);

private:
    int sockfd_; // the socket file descriptor
};

#endif
