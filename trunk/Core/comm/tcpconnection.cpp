#include "tcpconnection.h"

bool TCPConnection::ReadMessage(int sock, ServerMessage& sm)
{
	char buff[ServerMessage::SM_MAX_SIZ];
	memset(buff, 0, ServerMessage::SM_MAX_SIZ);
	if (SocketWrapper::Read(sock, buff, ServerMessage::SM_HEADERSIZE)) //Read clientID, msgLen, msgType
	{
		sm.SetClientID(buff[0]);
		sm.SetMsgLen(buff[1]);
		sm.SetMsgType((ServerMessage::MessageType) buff[2]);
		if(!SocketWrapper::Read(sock, buff, sm.GetMsgLen() - ServerMessage::SM_HEADERSIZE))
			return false;
		sm.SetData(buff);
		return true;
	}
	return false;
}

bool TCPConnection::WriteMessage(int sock, ServerMessage& sm)
{
	char buff[ServerMessage::SM_MAX_SIZ];
	memset(buff, 0, ServerMessage::SM_MAX_SIZ);
	size_t siz = sm.Serialize(buff);
	return SocketWrapper::Write(sock, buff, siz);
}
