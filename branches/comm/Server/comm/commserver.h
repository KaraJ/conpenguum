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
#include "../../Core/comm/data/clientaction.h"
#include "../../Core/comm/data/updateobject.h"
#include "../../Core/comm/data/servermessage.h"

class CommServer
{
public:
    static CommServer* Instance();

    inline bool hasNextClientAction() { return !actions_.empty(); }
    inline std::string nexthasNextClientAction()
    {
        ClientAction action = actions_.front();
        actions_.pop();
        return "";
    }
    inline bool hasNextServerMessage() { return !serverMsgs_.empty(); }
    inline ServerMessage nextServerMessage()
    {
        ServerMessage serverMsg = serverMsgs_.front();
        serverMsgs_.pop();
        return serverMsg;
    }
    void sendUpdate(const UpdateObject update);
    void sendServerMsg(const std::string msg);
private:
    CommServer() {}
    CommServer(const CommServer& cpy);
    CommServer& operator=(const CommServer& cc);
    ~CommServer();

    std::queue<ClientAction> actions_;
    std::queue<ServerMessage> serverMsgs_;
};

#endif
