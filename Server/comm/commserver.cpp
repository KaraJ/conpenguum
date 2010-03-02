/*----------------------------------------------------------------------------------------------------------
 --  SOURCE FILE: commserver.cpp
 --
 --  PROGRAM: TuxSpace
 --
 --  METHODS:
 --      void sendUpdate(const UpdateObject update);
 --      void sendServerMsg(const string msg);
 --
 --  PROGRAMMER: Ben Barbour
 --
 --  REVISIONS (date and description):
 --
 --  DATE: 2010-01-23
 --
 --  NOTES: Singleton - retrieve reference through CommServer::Instance()
 ----------------------------------------------------------------------------------------------------------*/
#include "commserver.h"

using namespace std;

CommServer::CommServer()
{
	tcpServer_ = new TCPServer();
	udpConnection_ = new UDPConnection();
	sem_init(&semSM_, 0, 1);
}

CommServer* CommServer::Instance()
{
    static CommServer* instance_ = 0;
	if(!instance_)
		instance_ = new CommServer();

	return instance_;
}

void CommServer::init()
{
	tcpServer_->Init(TCP_PORT);
	tcpServer_->StartReadThread(&serverMsgs_, &clients_, &semSM_);
	pthread_create(&readThread_, NULL, CommServer::readThreadFunc, NULL);
}

CommServer::~CommServer()
{
    delete tcpServer_;
    delete udpConnection_;
    pthread_join(readThread_, NULL);
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: sendUpdate
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --  UpdateObject update:    the UpdateObject to send
 --  int* clientIDs:         a pointer to an array of clientID's to send the update to
 --  int numClients:         the number of clients in clientIDs
 ----------------------------------------------------------------------------------------------------------*/
void CommServer::sendUpdate(const UpdateObject& update, const vector<int>& clientIDs)
{
    BYTE* buffer;
    update.serialize(&buffer);
	for (size_t i = 0; i < clientIDs.size(); i++)
	{
	    sockaddr_in to;
	    bzero(&to, sizeof(to));
	    to.sin_addr = clients_[clientIDs[i]];
	    to.sin_family = AF_INET;
	    to.sin_port = htons(UDP_PORT);
	    udpConnection_->sendMessage((sockaddr*)&to, buffer, UpdateObject::serializeSize);
	}
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: sendServerMsg
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --  string msg:     the message to send
 --  int* clientIDs: a pointer to an array of clientID's to send the message to. Use null to send to all.
 --  int numClients: the number of clients in clientIDs. If clientIDs = null, this is ignored.
 ----------------------------------------------------------------------------------------------------------*/
void CommServer::sendServerMsg(const ServerMessage& sm, const vector<int>& clients)
{
	/*for (int i = 0; i < numClients; ++i)
	{
		sm.SetClientID(clientID[i]);

	}*/
}

bool CommServer::hasNextClientAction()
{
    return !actions_.empty();
}

ClientAction CommServer::nextClientAction()
{
    ClientAction action = actions_.front();
    actions_.pop();
    return action;
}

bool CommServer::hasNextServerMessage()
{
	bool result;
	sem_wait(&semSM_);
    result = !serverMsgs_.empty();
    sem_post(&semSM_);
    return result;
}

ServerMessage CommServer::nextServerMessage()
{
	ServerMessage serverMsg;
	sem_wait(&semSM_);
    serverMsg = serverMsgs_.front();
    serverMsgs_.pop();
    sem_post(&semSM_);
    return serverMsg;
}

void* CommServer::readThreadFunc(void* args)
{
	while (true)
	{
		BYTE* buffer;
		ssize_t size = CommServer::Instance()->udpConnection_->recvMessage(&buffer);
		if (size == -1)
			break;
		else if (size == ClientAction::serializeSize)
		{
			ClientAction action(buffer);
			CommServer::Instance()->actions_.push(action);
		}
		else
			Logger::LogNContinue("Bad packet size received");
	}

    return 0;
}
