/*----------------------------------------------------------------------------------------------------------
--  SOURCE FILE: commserver.h
--
--  PROGRAM: TuxSpace
--
--  METHODS:
--      inline bool hasNextClientAction() { return !actions_.empty(); }
--      inline string nexthasNextClientAction()
--      inline bool hasNextServerMessage() { return !serverMsgs_.empty(); }
--      inline string nextServerMessage()
--
--  PROGRAMMER: Ben Barbour
--
--  REVISIONS (date and description):
--
--  DATE: 2010-01-23
--
--  NOTES: Singleton - retrieve reference through CommServer::Instance()
----------------------------------------------------------------------------------------------------------*/

#ifndef COMMSERVER_H
#define COMMSERVER_H

#include <string>
#include <queue>
#include <semaphore.h>

#include "comm/data/clientaction.h"
#include "comm/data/updateobject.h"
#include "comm/data/servermessage.h"
#include "TCPServer.h"
#include "comm/udpConnection.h"
#include "comm/crc.h"

class UDPConnection;

class CommServer
{
public:
    static CommServer* Instance();

    void init();
    bool hasNextClientAction();
    ClientAction nextClientAction();
    bool hasNextServerMessage();
    ServerMessage nextServerMessage();
    void sendUpdate(const UpdateObject update, const int* clientIDs, int numClients);
    void sendServerMsg(const std::string msg, const int* clientIDs, int numClients);

private:
    CommServer();
    CommServer(const CommServer& cpy);
    CommServer& operator=(const CommServer& cc);
    ~CommServer();
    static void* readThreadFunc(void* args);

    std::queue<ClientAction> actions_;
    std::queue<ServerMessage> serverMsgs_;
    TCPServer* tcpServer_;
    UDPConnection* udpConnection_;
    pthread_t readThread_;
    std::queue<sockaddr_in> clients_;
    sem_t semSM_;
};

#endif
