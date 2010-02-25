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

	void Serialize(char *data);
    ServerMessage() { }
    int  GetClientID() { return clientID; }
    void SetClientID(int id) { clientID = id; }
    int  GetMsgType() { return msgType; }
    void SetMsgType(MessageType type) { msgType = type;}
    std::string GetData() { return msgData; }
    void SetData(std::string data) { msgData = data.substr(0, BUFFSIZ); }
    size_t GetDataLen() { return msgData.length(); }

private:
    int clientID;
    MessageType msgType;
    std::string msgData;
};

#endif // SERVERMESSAGE_H
