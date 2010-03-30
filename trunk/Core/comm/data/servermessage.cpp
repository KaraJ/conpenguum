#include "servermessage.h"

using std::string;

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: ServerMessage::Serialize
--
-- DATE: 2010-02-23
--
-- INTERFACE:
--		char* data:	the data to save the ServerMessage into.
--
-- RETURN: The length of the  serialized data.
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: ServerMessage::SetData
--
-- DATE: 2010-02-23
--
-- INTERFACE:
--	string data:	The data portion of the ServerMessage
--
-- RETURN:	void
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/
void ServerMessage::SetData(string data)
{
	msgData = data.substr(0, SM_MAX_DATA);
	msgLen = msgData.length() + SM_HEADERSIZE;
}
