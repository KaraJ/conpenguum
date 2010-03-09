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
#include "comm/globals.h"
#include "comm/data/servermessage.h"
#include "Logger.h"
#include "comm/tcpconnection.h"

class TCPClient
{
public:
    bool Connect(const std::string& ip);
    void StartRdThread(std::queue<ServerMessage> *msgBuff, sem_t *semSM);
    ServerMessage Login(std::string playerName);
    void SendMessage(std::string message);
    bool IsConnected();
    void Logout();

private:
    static void* ReadThread(void*);

    static bool connected_;
    static std::queue<ServerMessage> *msgBuff_;
    static sem_t *semSM_;

    int  tcpSocket;
    pthread_t rThread_;
};

#endif // TCPCLIENT_H
