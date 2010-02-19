#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include "../../Core/comm/socketwrapper.h"
#include "../../Core/comm/globals.h"
#include <strings.h>
#include <arpa/inet.h>

class UDPClient
{
public:
	UDPClient(char* addr);
	~UDPClient();
	void recvMessage(void * buff);
	void sendMessage(const void* data, size_t dataLen);
private:
	int sockfd_;
	struct sockaddr_in servaddr;
};

#endif
