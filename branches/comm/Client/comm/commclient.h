/*----------------------------------------------------------------------------------------------------------
--  SOURCE FILE: commclient.h
--
--  PROGRAM: TuxSpace
--
--  METHODS:
--      inline bool isConnected()
--      inline bool hasNextUpdate()
--      inline UpdateObject nextUpdate()
--      inline bool hasNextChatMessage()
--      inline string nextChatMessage()
--      inline bool hasNextServerMessage()
--      inline string nextServerMessage()
--
--  PROGRAMMER: Ben Barbour
--
--  REVISIONS (date and description):
--
--  DATE: 2010-01-23
--
--  NOTES: Singleton - retrieve reference through CommClient::Instance()
----------------------------------------------------------------------------------------------------------*/

#ifndef COMMCLIENT_H
#define COMMCLIENT_H

//System Includes
#include <string>
#include <queue>

//User Includes
#include "tcpclient.h"
#include "comm/data/updateobject.h"
#include "comm/data/clientaction.h"
#include "comm/data/servermessage.h"
#include "udpClient.h"

class CommClient
{
public:
    static CommClient* Instance();

    inline bool isConnected() { return isConnected_; }
    inline bool hasNextUpdate() { return !updates_.empty(); }
    inline UpdateObject nextUpdate();
    inline bool hasNextChatMessage() { return !chatMsgs_.empty(); }
    inline ServerMessage nextChatMessage();
    inline bool hasNextServerMessage() { return !serverMsgs_.empty(); }
    inline ServerMessage nextServerMessage();
    int connect(const std::string playerName, const std::string address);
    void disconnect();
    void sendChat(const std::string msg, int id);
    void sendServerMsg(const std::string msg);
    void sendAction(const ClientAction action);

private:
    CommClient() {}
    CommClient(const CommClient& cpy);
    CommClient& operator=(const CommClient& cc);
    ~CommClient();

    UDPClient *udpClient_;
    std::queue<UpdateObject> updates_;
    std::queue<ServerMessage> chatMsgs_;
    std::queue<ServerMessage> serverMsgs_;
    bool isConnected_;
    TCPClient* tcpClient_;
};

#endif
