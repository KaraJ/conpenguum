#ifndef SERVERMESSAGE_H
#define SERVERMESSAGE_H

#include <string>

enum MessageType
{
    MT_LOGIN    = 1,
    MT_LOGOUT   = 2,
    MT_DEATH    = 3, /* Begins with comma seperated explosion location */
    MT_SHUTDOWN = 4, /* Server going down */
    MT_INIT     = 5, /* Initial message holding ScoreBoard and ClientID to Player Name mapping */
    MT_CHAT     = 6
};

class ServerMessage
{
public:
    ServerMessage();

private:
    int type;
    std::string data;
};

#endif // SERVERMESSAGE_H
