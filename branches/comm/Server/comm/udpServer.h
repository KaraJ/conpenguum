#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <cstring>
#include <sys/socket.h>

class UDPServer
{
public:
    UDPServer();
    void sendMessage(struct sockaddr* to, const void* data, size_t dataLen);
private:
    int sockfd_;
};

#endif
