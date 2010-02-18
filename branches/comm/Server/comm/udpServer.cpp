#include "udpServer.h"

UDPServer::UDPServer()
{
    struct sockaddr_in servaddr;

    this->sockfd_ = SocketWrapper::Socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(UDP_PORT);

    SocketWrapper::Bind(this->sockfd_, (struct sockaddr *)&servaddr, sizeof(sockaddr_in));
}

void UDPServer::sendMessage(struct sockaddr* to, const void* data, size_t dataLen)
{
	SocketWrapper::Sendto(this->sockfd_, data, dataLen, 0, to, sizeof(struct sockaddr));
}
