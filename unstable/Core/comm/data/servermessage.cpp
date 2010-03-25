#include "servermessage.h"

size_t ServerMessage::Serialize(char *data)
{
	size_t i;

	data[0] = (uint8) clientID;
	data[1] = (uint8) msgLen;
	data[2] = (uint8) msgType;

	for (i = 0; i < msgData.length(); ++i)
		data[i + SM_HEADERSIZE] = msgData[i];

	i += SM_HEADERSIZE;
	data[i] = 0;

	return i;
}

void ServerMessage::SetData(std::string data)
{
	msgData = data.substr(0, SM_MAX_DATA);
	msgLen = msgData.length() + SM_HEADERSIZE;
}
