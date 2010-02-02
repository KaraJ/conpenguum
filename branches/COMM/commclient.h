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

#include <string>
#include <queue>

#include "updateobject.h"
#include "clientaction.h"
#include "servermessage.h"

using std::string;
using std::queue;

class CommClient
{
public:
    static CommClient* Instance();

    inline bool isConnected() { return isConnected_; }
    inline bool hasNextUpdate() { return !updates_.empty(); }
    inline UpdateObject nextUpdate()
    {
        UpdateObject update = updates_.front();
        updates_.pop();
        return update;
    }
    inline bool hasNextChatMessage() { return !chatMsgs_.empty(); }
    inline string nextChatMessage()
    {
        string chatMsg = chatMsgs_.front();
        chatMsgs_.pop();
        return chatMsg;
    }
    inline bool hasNextServerMessage() { return !serverMsgs_.empty(); }
    inline string nextServerMessage()
    {
        string serverMsg = serverMsgs_.front();
        serverMsgs_.pop();
        return serverMsg;
    }
    int connect(const string name, const string address);
    void disconnect();
    void sendChat(const string msg, int id);
    void sendServerMsg(const string msg);
    void sendAction(const ClientAction action);

private:
    CommClient() {}
    CommClient(const CommClient& cpy);
    CommClient& operator=(const CommClient& cc);
    ~CommClient();

    queue<UpdateObject> updates_;
    queue<ServerMessage> chatMsgs_;
    queue<ServerMessage> serverMsgs_;
    bool isConnected_;
};

#endif
