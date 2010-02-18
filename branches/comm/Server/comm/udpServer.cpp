#include "udpServer.h"

UDPServer::UDPServer()
{
    struct sockaddr_in servaddr;
    this->sockfd_ = SocketWrapper::Socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(UDP_PORT);
}

void sendMessage(struct sockaddr* to, const void* data, size_t dataLen)
{

}
