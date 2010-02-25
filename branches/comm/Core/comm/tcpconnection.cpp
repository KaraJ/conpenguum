#include "tcpconnection.h"

using namespace std;

void TCPConnection::ReadMessage(int sock, ServerMessage& sm)
{
	char buff[TCP_MAXMSG];
	SocketWrapper::Read(sock, buff, 3); //Read clientID, msgLen, msgType
	sm.SetClientID(buff[0]);
	sm.SetMsgLen(buff[1]);
	sm.SetMsgType((ServerMessage::MessageType) buff[2]);
	SocketWrapper::Read(sock, buff, sm.GetMsgLen());
	sm.SetData(buff);
}

void TCPConnection::WriteMessage(int sock, ServerMessage& sm)
{
	char buff[TCP_MAXMSG];
	size_t siz = sm.Serialize(buff);
	SocketWrapper::Write(sock, buff, siz);
}
