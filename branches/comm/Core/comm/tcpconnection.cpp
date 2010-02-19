#include "tcpconnection.h"

using namespace std;

void TCPConnection::ReadMessage(int sock, ServerMessage& sm)
{
	int clientID, msgType;
	size_t dataLen;
	char buff[BUFFSIZ];

	SocketWrapper::Read(sock, &clientID, INTSIZ);
	SocketWrapper::Read(sock, &msgType, INTSIZ);
	SocketWrapper::Read(sock, &dataLen, INTSIZ);
	SocketWrapper::Read(sock, &buff, BUFFSIZ);

}

void TCPConnection::WriteMessage(int sock, ServerMessage& sm)
{
	int temp;
	const char *buff;

	buff = sm.GetData().c_str();
	temp = sm.GetClientID();
	SocketWrapper::Write(sock, &temp, INTSIZ);

	temp = sm.GetMsgType();
	SocketWrapper::Write(sock, &temp, INTSIZ);

	temp = sm.GetDataLen();
	SocketWrapper::Write(sock, &temp, INTSIZ);

	SocketWrapper::Write(sock, &buff, temp);
}
