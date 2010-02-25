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

CommServer* CommServer::Instance()
{
    static CommServer* instance_;
	if(!instance_)
		instance_ = new CommServer();

	return instance_;
}

void CommServer::init()
{
	tcpServer_ = new TCPServer();
	string buff = TCP_PORT;
	tcpServer_->Init(buff);
}

CommServer::CommServer()
{
    udpServer_ = new UDPServer();
    pthread_create(&readThread_, NULL, CommServer::readThreadFunc, NULL);
}

CommServer::~CommServer()
{
    delete tcpServer_;
    delete udpServer_;
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
void CommServer::sendUpdate(const UpdateObject update, const int* clientIDs, int numClients)
{
	//translate client IDs to sockaddr
	//convert UpdateOjbect to bytes
	//udpServer_.sendMessage(to, data, len);
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
void CommServer::sendServerMsg(const string msg, const int* clientIDs, int numClients)
{

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
    return !serverMsgs_.empty();
}

ServerMessage CommServer::nextServerMessage()
{
    ServerMessage serverMsg = serverMsgs_.front();
    serverMsgs_.pop();
    return serverMsg;
}

void* CommServer::readThreadFunc(void* args)
{
    BYTE* buffer;
    ssize_t size = CommServer::Instance()->udpServer_->recvMessage(&buffer);
    //if (size == ClientAction::serializeSize && CRC::CheckCRC(buffer, ClientAction::serializeSize))
    {
        ClientAction action(buffer);
        CommServer::Instance()->actions_.push(action);
    }
    //else
        //Logger::LogNContinue("Bad CRC received");
}
