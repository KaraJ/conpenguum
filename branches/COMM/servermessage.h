#ifndef SERVERMESSAGE_H
#define SERVERMESSAGE_H

class ServerMessage
{
public:
    ServerMessage();

private:
    int type; /* enum or define? LOGIN, LOGOUT, DEATH, SHUTDOWN, INIT, CHAT */
    string data;
};

#endif // SERVERMESSAGE_H
