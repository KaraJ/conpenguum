#ifndef SERVERMESSAGE_H
#define SERVERMESSAGE_H

#include <string>

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

    ServerMessage() { }
    int  GetClientID() { return clientID; }
    void SetClientID(int id) { clientID = id; }
    int  GetMsgType() { return msgType; }
    void SetMsgType(MessageType type) { msgType = type;}
    std::string GetData() { return msgData; }
    void SetData(std::string data) { msgData = data; }
    size_t GetDataLen() { return msgData.length(); }
    friend inline std::ostream& operator<<(std::ostream&, const Message&);

private:
    int clientID;
    MessageType msgType;
    std::string msgData;
};

std::ostream& operator<<(std::ostream& os, const ServerMessage& msg)
{
    return os << "Target: " << msg.clientID << "\nType: " << msg.msgType
            << "\nText: '" << msg.msgData << "'";
}

#endif // SERVERMESSAGE_H
