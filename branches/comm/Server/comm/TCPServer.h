#ifndef TCPSERVER_H_
#define TCPSERVER_H_

//System Includes
#include <netinet/in.h>
#include <sstream>
#include <queue>
#include <semaphore.h>
#include <strings.h>
#include <pthread.h>
#include <map>

//User Includes
#include "comm/data/servermessage.h"
#include "comm/socketwrapper.h"
#include "comm/globals.h"
#include "comm/tcpconnection.h"

class TCPServer
{
public:
	TCPServer();
	void Init(const std::string port);
	void StartReadThread(std::queue<ServerMessage> *serverMsgs, std::map<int,in_addr> *clients, sem_t *semSM);
	static void* ReadThread(void*);

private:
	int listenSocket_;
	static int clients_[32];
	static sem_t *semSM_;
	static std::queue<ServerMessage> *msgBuff_;
	static std::map<int,in_addr> *clientMap_;
	pthread_t rThread_;

};

#endif /* TCPSERVER_H_ */
