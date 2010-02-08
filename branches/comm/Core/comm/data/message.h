#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message
{
private:
    std::string text;
    int ClientID;

public:
    Message(int, std::string);
    virtual unsigned char[] Serialize() = 0;
};

#endif // MESSAGE_H
