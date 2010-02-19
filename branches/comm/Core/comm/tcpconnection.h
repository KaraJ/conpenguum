#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

//System Includes

//User Includes
#include "data/servermessage.h"
#include "socketwrapper.h"

//User Definitions
#define BUFFSIZ 1024
#define INTSIZ  4

class TCPConnection
{
public:
    static void ReadMessage(int sock, ServerMessage& sm);
    static void WriteMessage(int sock, ServerMessage& sm);

private:
    TCPConnection() {}

};

#endif // TCPCONNECTION_H
