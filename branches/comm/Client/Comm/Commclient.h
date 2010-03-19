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
#include "Tcpclient.h"
#include "../Core/comm/data/updateobject.h"
#include "../Core/comm/data/clientaction.h"
#include "../Core/comm/data/servermessage.h"
#include "../Core/comm/udpConnection.h"

class UDPConnection;

class CommClient
{
public:
    static CommClient* Instance();

    inline bool isConnected() { return isConnected_; }
    bool hasNextUpdate();
    UpdateObject nextUpdate();
    bool hasNextServerMessage();
    ServerMessage nextServerMessage();
    int connect(const std::string playerName, const std::string address);
    void disconnect();
    void sendServerMsg(const std::string msg) throw (std::string);
    void sendAction(const ClientAction action);
    static void* readThreadFunc(void* args);

private:
    CommClient();
    CommClient(const CommClient& cpy);
    CommClient& operator=(const CommClient& cc);
    ~CommClient();
    pthread_t readThread_;

    UDPConnection *udpConnection_;
    struct sockaddr_in servAddr;
    std::queue<UpdateObject> updates_;
    std::queue<ServerMessage> serverMsgs_;
    sem_t semSM_;
    sem_t semUP_;
    bool isConnected_;
    size_t clientID_;
    TCPClient* tcpClient_;
};

#endif
