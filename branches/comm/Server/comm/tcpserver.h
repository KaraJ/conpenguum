#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <map>
#include "message.h"

#define MAXPENDING 5    /* Max connection requests */
#define BUFFSIZE 32

/*typedef struct Connection
{
    int socket;
    int
} Connection;*/

class TCPServer
{
public:
    explicit TCPServer(int port = 8001);
    void Run();
    void SendMesssage(Message);
    
private:
    static void Die(std::string mess) { perror(mess.c_str()); exit(1); }
    friend void* ConnectThread(void*);
    friend void* StatsThread(void*);

private:
    int serversock;
    struct sockaddr_in echoserver;
    static int numConnected;
    static long numMsgs;
    std::map<int, int*> sockets;
};

#endif
