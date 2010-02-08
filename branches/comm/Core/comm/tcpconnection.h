#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

//This class to hold low-level protocol specific functionality
#include <string>
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */

class TCPConnection
{
public:
    TCPConnection GetInstance();
    std::string HostToIp();
    bool Connect();
    bool Close();
    bool ReadMessage();
    bool WriteMessage();

private:
    TCPConnection();
    struct sockaddr sa;

};

#endif // TCPCONNECTION_H
