#ifndef SERVERMESSAGE_H
#define SERVERMESSAGE_H

#include <string>

class ServerMessage
{
public:
    ServerMessage() { }
    int  GetClientID() { return clientID; }
    void SetClientID(int id) { clientID = id; }
    int  GetMsgType() { return msgType; }
    void SetMsgType(int type) { msgType = type;}
    std::string GetData() { return msgData; }
    void SetData(std::string data) { msgData = data; }
    size_t GetDataLen() { return msgData.length(); }

    enum MessageType
    {
    	MT_LOGIN    = 1,
    	MT_LOGOUT   = 2,
    	MT_DEATH    = 3, /* Begins with comma separated explosion location */
    	MT_SHUTDOWN = 4, /* Server going down */
    	MT_INIT     = 5, /* Initial message holding ScoreBoard and ClientID to Player Name mapping */
    	MT_CHAT     = 6
    };

private:
    int clientID;
    int msgType;
    std::string msgData;
};

#endif // SERVERMESSAGE_H
