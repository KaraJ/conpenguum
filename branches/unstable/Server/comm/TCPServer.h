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

#include <iostream>

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
    void SendLogoutMessage(int clientId);
	void ClientDC(int);
	void setClientActive(int clientID, bool active){activeClients[clientID] = active;}
	bool isClientActive(int clientID){return activeClients[clientID];}

private:
	int listenSocket_;
	fd_set allSet_;
	int maxClientSocket_;
	int clientSockets_[MAX_CLIENTS];
	sem_t *semSM_;
	std::queue<ServerMessage> *msgBuff_;
	std::map<int,in_addr> *clientAddressMap_;
	pthread_t rThread_;
	bool activeClients[MAX_CLIENTS];

};

#endif /* TCPSERVER_H_ */
