#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include "comm/socketwrapper.h"
#include "comm/globals.h"
#include "comm/data/updateobject.h"
#include "commclient.h"
#include "comm/data/crc.h"
#include <strings.h>
#include <arpa/inet.h>
#include <pthread.h>

class UDPClient
{
public:
	UDPClient(const char* addr);
	~UDPClient();
	void recvMessage(BYTE* buff);
	void sendMessage(const BYTE* data, size_t dataLen);
private:
	int sockfd_;
	struct sockaddr_in servaddr;
	pthread_t readThread;
};
void* ReadThread(void* args);


#endif
