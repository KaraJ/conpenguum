#include "tcpconnection.h"

using namespace std;

void TCPConnection::ReadMessage(int sock, ServerMessage& sm)
{
	char buff[TCP_MAXMSG];
	SocketWrapper::Read(sock, buff, TCP_MAXMSG);

}

void TCPConnection::WriteMessage(int sock, ServerMessage& sm)
{
	char buff[TCP_MAXMSG];

	sm.Serialize(buff);

}
