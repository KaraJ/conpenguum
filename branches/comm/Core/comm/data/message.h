#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message
{
private:
    int ClientID;
    std::string text;

public:
    Message(int, std::string);
    //virtual unsigned char[] Serialize() = 0;
};

#endif // MESSAGE_H
