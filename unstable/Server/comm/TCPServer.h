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
#include "../Core/comm/data/servermessage.h"
#include "../Core/comm/socketwrapper.h"
#include "../Core/comm/globals.h"
#include "../Core/comm/tcpconnection.h"

class TCPServer
{
public:
	TCPServer();
	void Init(const std::string port);
	void StartReadThread(std::queue<ServerMessage> *serverMsgs, std::map<int,in_addr> *clients, sem_t *semSM);
	void SendMessage(ServerMessage msg);
	void SendMessageToAll(ServerMessage msg);
	static void* ReadThread(void*);

private:
	static void ClientDC(int, int);

private:
	int listenSocket_;
	static fd_set allSet_;
	static int maxClientSocket_;
	static int clientSockets_[MAX_CLIENTS];
	static sem_t *semSM_;
	static std::queue<ServerMessage> *msgBuff_;
	static std::map<int,in_addr> *clientAddressMap_;
	pthread_t rThread_;

};

#endif /* TCPSERVER_H_ */
