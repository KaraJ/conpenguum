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
#include <map>
#include <semaphore.h>
#include <vector>

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
    void sendServerMsg(ServerMessage msg, const std::vector<int>& clients);
    void sendServerMsg(const ServerMessage& msg);
    void sendUpdate(const UpdateObject& update, const std::vector<int>& clientIDs);
    void sendUpdateToAll(const UpdateObject& update);

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
    std::map<int,in_addr> clients_;
    sem_t semSM_;
};

#endif
