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
#include <semaphore.h>
#include <arpa/inet.h>

//User Includes
#include "tcpclient.h"
#include "comm/data/updateobject.h"
#include "comm/data/clientaction.h"
#include "comm/data/servermessage.h"
#include "comm/udpConnection.h"

class UDPConnection;

class CommClient
{
public:
    static CommClient* Instance();

    inline bool isConnected() { return isConnected_; }
    inline bool hasNextUpdate() { return !updates_.empty(); }
    UpdateObject nextUpdate();
    void addUpdate(UpdateObject update);
    inline bool hasNextServerMessage();
    ServerMessage nextServerMessage();
    int connect(const std::string playerName, const std::string address);
    void disconnect();
    void sendServerMsg(const std::string msg) throw (std::string);
    void sendAction(const ClientAction action);

private:
    CommClient() { sem_init(&semSM_, 0, 1); }
    CommClient(const CommClient& cpy);
    CommClient& operator=(const CommClient& cc);
    ~CommClient();

    UDPConnection *udpConnection_;
    struct sockaddr_in servAddr;
    std::queue<UpdateObject> updates_;
    std::queue<ServerMessage> serverMsgs_;
    sem_t semSM_;
    bool isConnected_;
    TCPClient* tcpClient_;
};

#endif
