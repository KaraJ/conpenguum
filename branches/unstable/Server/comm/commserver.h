#ifndef COMMSERVER_H
#define COMMSERVER_H

#include <queue>
#include <map>
#include <semaphore.h>
#include <vector>
#include <signal.h>

#include "../../Core/comm/data/clientaction.h"
#include "../../Core/comm/data/updateobject.h"
#include "../../Core/comm/data/servermessage.h"
#include "TCPServer.h"
#include "../Core/comm/udpConnection.h"
#include "../../Core/comm/crc.h"

class UDPConnection;

class CommServer
{
public:
	//get the instance of the CommServer
    static CommServer* Instance();

    //start the server
    void init(const std::string &port);

    //read the queues
    bool hasNextClientAction();
    ClientAction nextClientAction();
    bool hasNextServerMessage();
    ServerMessage nextServerMessage();

    //send messages or updates
    void sendServerMsg(ServerMessage msg, const std::vector<size_t>& clients);
    void sendServerMsg(const ServerMessage& msg);
    void sendUpdate(const UpdateObject& update, const std::vector<int>& clientIDs);
    void sendUpdateToAll(const UpdateObject& update);
    void Shutdown();
private:
    CommServer();
    ~CommServer();
    CommServer(const CommServer& cpy);
    CommServer& operator=(const CommServer& cc);
    static void* readThreadUDP(void* args);

    std::queue<ClientAction> actions_;
    std::queue<ServerMessage> serverMsgs_;
    TCPServer* tcpServer_;
    UDPConnection* udpConnection_;
    pthread_t readThread_;
    std::map<int,in_addr> clients_;
    sem_t semSM_;
    sem_t semUDP_;
};

#endif
