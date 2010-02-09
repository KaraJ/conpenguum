#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <vector>
#define BYTE unsigned char

enum MessageType {
    MT_LOGIN = 1,
    MT_LOGOUT = 2,
    MT_DEATH = 3, /* Begins with comma seperated explosion location */
    MT_SHUTDOWN = 4, /* Server going down */
    MT_INIT = 5, /* Initial message holding ScoreBoard and ClientID to Player Name mapping */
    MT_CHAT = 6
};

class Message {
public:

    Message(int targetID, MessageType type, std::string text)
    : clientID(targetID), mType(type), mText(text) {
    }

    Message(std::vector<BYTE> data) {
        size_t i;
        clientID = (int) data[0];
        mType = (MessageType) data[1];
        for (i = 0; i < data.size() - 2; i++)
            mText += (char) data[i + 2];
    }

    Message(char data[]) {
        size_t i;
        if (strlen(data) > 2) {
            clientID = (int) data[0];
            mType = (MessageType) data[1];
            for (i = 0; i < strlen(data) - 2; i++)
                mText += (char) data[i + 2];
        }
    }

    const char *Serialize() {
        char *data = (char*)malloc(sizeof(char) * GetLength());
        size_t i;        
        data[0] = (BYTE) clientID;
        data[1] = (BYTE) mType;
        for (i = 0; i < mText.length(); i++)
            data[i + 2] = mText[i];

        return data;
    }

    int GetID() {
        return clientID;
    }

    int GetLength() {
        return (mText.length() + 2);
    }

    MessageType GetType() {
        return mType;
    }

    std::string GetText() {
        return mText;
    }
    friend inline std::ostream & operator<<(std::ostream&, const Message&);

private:
    int clientID;
    MessageType mType;
    std::string mText;
};

std::ostream & operator<<(std::ostream& os, const Message& msg) {
    return os << "Target: " << msg.clientID << "\nType: " << msg.mType
            << "\nText: '" << msg.mText << "'";
}

#endif
