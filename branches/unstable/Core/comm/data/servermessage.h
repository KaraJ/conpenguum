#ifndef SERVERMESSAGE_H
#define SERVERMESSAGE_H

//System Includes
#include <string>

class ServerMessage
{
public:
	typedef unsigned char uint8;
	enum MessageType
	    {
	    	MT_LOGIN    = 1,
	    	MT_DEATH    = 2, // Begins with comma separated explosion location
	    	MT_SHUTDOWN = 3, // Server going down
	    	MT_INIT     = 4, // Initial message holding ScoreBoard and ClientID to Player Name mapping
	    	MT_CHAT     = 5, // Basic chat message
	    	MT_LOGOUT	= 6, // Logout (not actually sent, created on disconnect)
	    	MT_FULL		= 7, // Server full
	    	MT_SCORES	= 8  // Sends current scoreboard
	    };
    static const int SM_HEADERSIZE = 3;								//Header size
	static const int SM_MAX_DATA = 1024;							//Maximum Data portion size
	static const int SM_MAX_SIZ = (SM_MAX_DATA +  SM_HEADERSIZE);	//Maximum Total ServerMessage size

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
