#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

//This class to hold low-level protocol specific functionality

class TCPConnection
{
public:
    GetInstance();
    HostToIp();
    Connect();
    Close();
    ReadMessage();
    WriteMessage();

private:
    TCPConnection();
    struct sock_addr sa;
};

#endif // TCPCONNECTION_H
