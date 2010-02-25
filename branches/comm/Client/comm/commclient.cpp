/*----------------------------------------------------------------------------------------------------------
 --  SOURCE FILE: commclient.cpp
 --
 --  PROGRAM: TuxSpace
 --
 --  METHODS:
 --      bool connect(const string name, const string address)
 --      void disconnect()
 --      void sendChat(const string msg, int toClientID)
 --      void sendServerMsg(const string msg)
 --      void sendAction(const ClientAction action)
 --
 --  PROGRAMMER: Ben Barbour
 --
 --  REVISIONS (date and description):
 --
 --  DATE: 2010-01-23
 --
 --  NOTES: Singleton - retrieve reference through CommClient::Instance()
 ----------------------------------------------------------------------------------------------------------*/

#include "commclient.h"

using namespace std;

CommClient* CommClient::Instance()
{
    static CommClient* instance_;
    if (!instance_)
        instance_ = new CommClient();
    return instance_;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: connect
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --  string name:    the player name
 --  string address: the address of the server, in dotted decimal format
 --
 -- RETURN: If connection was successful: your clientID (always > 0).
 --         If server could not be found: -1
 --         If that name is in use: -2
 --         If other network error: -3
 ----------------------------------------------------------------------------------------------------------*/
int CommClient::connect(const string name, const string address)
{
    if (!isConnected_)
    {
        tcpClient_ = new TCPClient();
        if (!tcpClient_->Connect(address))
        	return -1;
        serverMsgs_.push(tcpClient_->Login(name));
        tcpClient_->StartRdThread(&serverMsgs_, &semSM_);
        udpClient_ = new UDPClient(address.c_str());
        isConnected_ = true;
    }
    return 0;
}

void CommClient::addUpdate(UpdateObject update)
{
	updates_.push(update);
}

UpdateObject CommClient::nextUpdate()
{
    UpdateObject update = updates_.front();
    updates_.pop();
    return update;
}

ServerMessage CommClient::nextServerMessage()
{
	sem_wait(&semSM_);
    ServerMessage serverMsg = serverMsgs_.front();
    serverMsgs_.pop();
    sem_post(&semSM_);
    return serverMsg;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: disconnect
 --
 -- DATE: 2010-01-23
 --
 -- NOTES: Informs the server of disconnection, then disconnects from the server gracefully.
 ----------------------------------------------------------------------------------------------------------*/
void CommClient::disconnect()
{
    if (isConnected_)
    {
        delete tcpClient_;
        delete udpClient_;
        tcpClient_ = 0;
        udpClient_ = 0;
        isConnected_ = false;
    }
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: sendChat
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --  string msg:     the message to send
 --  int toClientID: the clientID (or teamID, in a team match) to send to
 ----------------------------------------------------------------------------------------------------------*/
void CommClient::sendChat(const string msg, int id)
{
    if (isConnected_)
    {
        //@todo send chat messages
    }
    else
    {
        //@todo throw exception
    }
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: sendServerMsg
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --  string msg:     the message to send to send to the server
 ----------------------------------------------------------------------------------------------------------*/
void CommClient::sendServerMsg(const string msg) throw (string)
{
    if (isConnected_)
    	tcpClient_->SendMessage(msg);
    else
        throw "CommClient::Not Connected";
}

bool CommClient::hasNextServerMessage()
{
	bool result;
	sem_wait(&semSM_);
	result = !serverMsgs_.empty();
	sem_post(&semSM_);
	return result;
}
/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: sendAction
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --  ClientAction action:    the action to send to the server (should send one every frame
 ----------------------------------------------------------------------------------------------------------*/
void CommClient::sendAction(ClientAction action)
{
    BYTE* buffer = 0;
    if (isConnected_)
    {
        action.serialize(&buffer);
        udpClient_->sendMessage(buffer, ClientAction::serializeSize);
    }
    else
    {
        //@todo throw exception
    }
}
