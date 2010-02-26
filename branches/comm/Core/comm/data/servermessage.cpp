#include "servermessage.h"

size_t ServerMessage::Serialize(char *data)
{
	size_t i;

	data[0] = (BYTE) clientID;
	data[1] = (BYTE) msgLen;
	data[2] = (BYTE) msgType;

	for (i = 0; i < msgData.length() + 1; ++i)
		data[i + 3] = msgData[i];

	return i;
}

void ServerMessage::SetData(std::string data)
{
	msgData = data.substr(0, BUFFSIZ);
	msgLen = data.length() + 4;
}
