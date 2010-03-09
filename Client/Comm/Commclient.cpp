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

#include "Commclient.h"

using namespace std;

CommClient::CommClient()
{
	sem_init(&semSM_, 0, 1);
	tcpClient_ = new TCPClient();
}

CommClient* CommClient::Instance()
{
    static CommClient* instance_ =0;
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

        if (!tcpClient_->Connect(address))
        	return -1;
        serverMsgs_.push(tcpClient_->Login(name));
        clientID_ = serverMsgs_.front().GetClientID();
        tcpClient_->StartRdThread(&serverMsgs_, &semSM_);

        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(UDP_PORT);
        if (inet_pton(AF_INET, address.c_str(), &servAddr.sin_addr) != 1)
            Logger::LogNQuit("Error connection client - bad IP");
        udpConnection_ = new UDPConnection();
        isConnected_ = true;
        pthread_create(&readThread_, NULL, CommClient::readThreadFunc, NULL);
    }
    return 0;
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
        delete udpConnection_;
        tcpClient_ = 0;
        udpConnection_ = 0;
        isConnected_ = false;
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
        udpConnection_->sendMessage((sockaddr*)&this->servAddr, buffer, ClientAction::serializeSize);
    }
    else
    {
        //@todo throw exception
    }
}

void* CommClient::readThreadFunc(void* args)
{
    BYTE* buffer;
    ssize_t size = CommClient::Instance()->udpConnection_->recvMessage(&buffer);
    if (size == UpdateObject::serializeSize)
    {
        UpdateObject update(buffer);
        CommClient::Instance()->updates_.push(update);
    }
    else
        Logger::LogNContinue("Bad packet size received");

    return 0;
}
