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
#include "comm/data/clientaction.h"
#include "comm/data/updateobject.h"
#include "comm/data/servermessage.h"
#include "TCPServer.h"
#include "udpServer.h"

class CommServer
{
public:
    static CommServer* Instance();

    void init();
    bool hasNextClientAction();
    std::string nextClientAction();
    bool hasNextServerMessage();
    ServerMessage nextServerMessage();
    void sendUpdate(const UpdateObject update, const int* clientIDs, int numClients);
    void sendServerMsg(const std::string msg, const int* clientIDs, int numClients);

private:
    CommServer() {}
    CommServer(const CommServer& cpy);
    CommServer& operator=(const CommServer& cc);
    ~CommServer();

    std::queue<ClientAction> actions_;
    std::queue<ServerMessage> serverMsgs_;
    TCPServer *tcpServer_;
    UDPServer udpServer_;
};

#endif
