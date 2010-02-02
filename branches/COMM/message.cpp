#include "message.h"

Message::Message(int _ClientID, std::string _text)
    : ClientID(_ClientID), text(_text)
{
}
