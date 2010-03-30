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
#include "../Core/Logger.h"

class UDPConnection;

class CommClient
{
public:
	//get the commclient and connect or disconnect
    static CommClient* Instance();
    inline bool isConnected() { return isConnected_; }
    int connect(const std::string playerName, const std::string address, const std::string port);
    void disconnect();

    //access incoming updates and server messages
    bool hasNextUpdate();
    UpdateObject nextUpdate();
    bool hasNextServerMessage();
    ServerMessage nextServerMessage();

    //send outgoing actions and server messages
    void sendServerMsg(const std::string msg) throw (std::string);
    void sendAction(const ClientAction action);
private:
    //private constructors
    CommClient();
    CommClient(const CommClient& cpy);
    CommClient& operator=(const CommClient& cc);
    ~CommClient();

    UDPConnection *udpConnection_;
    TCPClient* tcpClient_;
    bool isConnected_;
    struct sockaddr_in servAddr;
    std::queue<UpdateObject> updates_;
    std::queue<ServerMessage> serverMsgs_;
    sem_t semTCP_;
    sem_t semUDP_;

    //UDP read thread
    pthread_t readThread_;
    static void* readThreadUDP(void* args);
};

#endif
