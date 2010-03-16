#include "tcpconnection.h"

using namespace std;

bool TCPConnection::ReadMessage(int sock, ServerMessage& sm)
{
	char buff[TCP_MAXMSG];
	if (SocketWrapper::Read(sock, buff, ServerMessage::SM_HEADERSIZE)) //Read clientID, msgLen, msgType
	{
		sm.SetClientID(buff[0]);
		sm.SetMsgLen(buff[1]);
		sm.SetMsgType((ServerMessage::MessageType) buff[2]);
		SocketWrapper::Read(sock, buff, sm.GetMsgLen() - ServerMessage::SM_HEADERSIZE);
		sm.SetData(buff);
		return true;
	}
	return false;
}

void TCPConnection::WriteMessage(int sock, ServerMessage& sm)
{
	char buff[TCP_MAXMSG];
	size_t siz = sm.Serialize(buff);
	SocketWrapper::Write(sock, buff, siz);
}
