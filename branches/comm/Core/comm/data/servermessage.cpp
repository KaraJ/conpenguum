#include "servermessage.h"

void ServerMessage::Serialize(char *data)
{
	size_t i;

	data[0] = (BYTE) clientID;
	data[1] = (BYTE) msgType;

	for (i = 0; i < msgData.length(); ++i)
		data[i + 2] = msgData[i];
}
