#ifndef SERVERMESSAGE_H
#define SERVERMESSAGE_H

#include <string>
#include "../globals.h"

class ServerMessage
{
public:
	enum MessageType
	    {
	    	MT_LOGIN    = 1,
	    	MT_LOGOUT   = 2,
	    	MT_DEATH    = 3, /* Begins with comma separated explosion location */
	    	MT_SHUTDOWN = 4, /* Server going down */
	    	MT_INIT     = 5, /* Initial message holding ScoreBoard and ClientID to Player Name mapping */
	    	MT_CHAT     = 6
	    };

	size_t Serialize(char *data);
    ServerMessage() { }
    size_t  GetClientID() { return clientID; }
    void SetClientID(size_t id) { clientID = id; }
    int  GetMsgType() { return msgType; }
    void SetMsgType(MessageType type) { msgType = type;}
    void SetMsgLen(size_t length) { msgLen = length; }
    size_t GetMsgLen() { return msgLen; }
    std::string GetData() { return msgData; }
    void SetData(std::string data);
    size_t GetDataLen() { return msgData.length(); }

private:
    size_t clientID;
    size_t msgLen;
    MessageType msgType;
    std::string msgData;
};

#endif // SERVERMESSAGE_H
