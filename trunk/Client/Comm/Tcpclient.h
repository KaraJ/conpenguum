#ifndef TCPCLIENT_H
#define TCPCLIENT_H

//System Includes
#include <netdb.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <queue>
#include <semaphore.h>

//User Includes
#include "../Core/comm/globals.h"
#include "../Core/comm/data/servermessage.h"
#include "../Core/Logger.h"
#include "../Core/comm/tcpconnection.h"

class TCPClient
{
public:
    bool Connect(const std::string& ip, const std::string& port);
    void Disconnect();
    void StartRdThread(std::queue<ServerMessage> *msgQueue, sem_t *semSM);
    ServerMessage Login(std::string playerName);
    void SendMessage(std::string message);
    bool IsConnected();
    void Logout();
    void setClientId(int id) { clientId_ = id; }

private:
    static void* ReadThread(void*);

    bool connected_;
    std::queue<ServerMessage> *msgBuff_;
    sem_t *semSM_;

    int tcpSocket_;
    int clientId_;
    pthread_t rThread_;
};

#endif // TCPCLIENT_H
