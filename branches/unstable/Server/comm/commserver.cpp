/*----------------------------------------------------------------------------------------------------------
 --  SOURCE FILE: commserver.cpp
 --
 --  PROGRAM: TuxSpace
 --
 --  METHODS:
 --		CommServer::CommServer()
 --		CommServer* CommServer::Instance()
 --		void CommServer::init()
 --		CommServer::~CommServer()
 --		void CommServer::sendUpdate(const UpdateObject& update, const vector<int>& clientIDs)
 --		void CommServer::sendUpdateToAll(const UpdateObject& update)
 --		void CommServer::sendServerMsg(ServerMessage sm, const vector<int>& clients)
 --		void CommServer::sendServerMsg(const ServerMessage& sm)
 --		bool CommServer::hasNextClientAction()
 --		ClientAction CommServer::nextClientAction()
 --		bool CommServer::hasNextServerMessage()
 --		ServerMessage CommServer::nextServerMessage()
 --		void* CommServer::readThreadUDP(void* args)
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

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::hasNextClientAction
 --
 -- DATE: 2010-01-23
 --
 -- NOTES: Private constructor for the CommServer. Should only be called the first time Instance is called.
 ----------------------------------------------------------------------------------------------------------*/
CommServer::CommServer()
{
    tcpServer_ = new TCPServer();
    udpConnection_ = new UDPConnection(UDP_PORT);
    sem_init(&semSM_, 0, 1);
    sem_init(&semUDP_, 0, 1);
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::Instance
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: The CommServer singleton.
 ----------------------------------------------------------------------------------------------------------*/
CommServer* CommServer::Instance()
{
    static CommServer* instance_ = 0;
    if (!instance_)
        instance_ = new CommServer();

    return instance_;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::init
 --
 -- DATE: 2010-01-23
 --
 -- NOTES: Should be called to start the server.
 ----------------------------------------------------------------------------------------------------------*/
void CommServer::init(const string &port)
{
    tcpServer_->Init(port);
    tcpServer_->StartReadThread(&serverMsgs_, &clients_, &semSM_);
    pthread_create(&readThread_, NULL, CommServer::readThreadUDP, NULL);
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::~CommServer
 --
 -- DATE: 2010-01-23
 ----------------------------------------------------------------------------------------------------------*/
CommServer::~CommServer()
{
    delete tcpServer_;
    delete udpConnection_;
    pthread_join(readThread_, NULL);
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::sendUpdate
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
    update.serialise(&buffer);
    for (size_t i = 0; i < clientIDs.size(); i++)
    {
        sockaddr_in to;
        bzero(&to, sizeof(to));
        to.sin_addr = clients_[clientIDs[i]];
        to.sin_family = AF_INET;
        to.sin_port = htons(UDP_PORT);
        udpConnection_->sendMessage((sockaddr*) &to, buffer, UpdateObject::serializeSize);
    }
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::sendUpdateToAll
 --
 -- DATE: 2010-03-09
 --
 -- INTERFACE:
 --  sendUpdateToAll(const UpdateObject& update)
 --     update: The update object to send to every connected client
 ----------------------------------------------------------------------------------------------------------*/
void CommServer::sendUpdateToAll(const UpdateObject& update)
{
    BYTE* buffer;
    update.serialise(&buffer);

    for (map<int, in_addr>::const_iterator it = clients_.begin(); it != clients_.end(); ++it)
    {
        sockaddr_in to;
        bzero(&to, sizeof(to));
        to.sin_addr = it->second;
        to.sin_family = AF_INET;
        to.sin_port = htons(UDP_PORT);
        udpConnection_->sendMessage((sockaddr*) &to, buffer, UpdateObject::serializeSize);
    }
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::sendServerMsg
 --
 -- DATE: 2010-01-23
 -- UPDATE: 2010-03-08
 --
 -- INTERFACE:
 --  ServerMessage sm: Message to send to clients
 --  const vector<int>& clients: Reference to vector of client ids to send message to - if NULL then
 --								 send to all clients
 ----------------------------------------------------------------------------------------------------------*/
void CommServer::sendServerMsg(ServerMessage sm, const vector<int>& clients)
{
    if (clients.size() == 0)
        tcpServer_->SendMessageToAll(sm);

    for (size_t i = 0; i < clients.size(); ++i)
    {
        sm.SetClientID(clients[i]);
        tcpServer_->SendMessage(sm);
    }
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::sendServerMsg
 --
 -- DATE: 2010-03-08
 --
 -- INTERFACE:
 --  ServerMessage sm: Message to send to client
 ----------------------------------------------------------------------------------------------------------*/
void CommServer::sendServerMsg(const ServerMessage& sm)
{
    tcpServer_->SendMessage(sm);
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::hasNextClientAction
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: If there is a ClientAction in the queue.
 ----------------------------------------------------------------------------------------------------------*/
bool CommServer::hasNextClientAction()
{
    sem_wait(&semUDP_);
    bool empty = actions_.empty();
    sem_post(&semUDP_);
    return !empty;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::nextClientAction
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: The client action in the front of the queue.
 ----------------------------------------------------------------------------------------------------------*/
ClientAction CommServer::nextClientAction()
{
    sem_wait(&semUDP_);
    ClientAction action = actions_.front();
    actions_.pop();
    sem_post(&semUDP_);
    return action;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::hasNextServerMessage
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: If there is a ServerMessage in the queue.
 ----------------------------------------------------------------------------------------------------------*/
bool CommServer::hasNextServerMessage()
{
    bool result;
    sem_wait(&semSM_);
    result = !serverMsgs_.empty();
    sem_post(&semSM_);
    return result;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::nextServerMessage
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: The ServerMessage in the front of the queue.
 ----------------------------------------------------------------------------------------------------------*/
ServerMessage CommServer::nextServerMessage()
{
    ServerMessage serverMsg;
    sem_wait(&semSM_);
    serverMsg = serverMsgs_.front();
    serverMsgs_.pop();
    sem_post(&semSM_);
    return serverMsg;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommServer::readThreadUDP
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --		void* args: NULL
 --
 --	RETURN: NULL
 --
 -- NOTES: The read thread for the UDP Server.
 ----------------------------------------------------------------------------------------------------------*/
void* CommServer::readThreadUDP(void* args)
{
    while (true)
    {
        BYTE* buffer;
        ssize_t size = CommServer::Instance()->udpConnection_->recvMessage(&buffer);
        if (size == -1)
            break;
        else if (size == ClientAction::serialiseSize)
        {
            ClientAction action(buffer);
            sem_wait(&CommServer::Instance()->semUDP_);
            CommServer::Instance()->actions_.push(action);
            sem_post(&CommServer::Instance()->semUDP_);
        }
        else
        {
            Logger::LogNContinue("Bad packet size received");
        }
    }

    return 0;
}
