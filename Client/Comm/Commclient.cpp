/*----------------------------------------------------------------------------------------------------------
 --  SOURCE FILE: commclient.cpp
 --
 --  PROGRAM: TuxSpace
 --
 --  METHODS:
 --
 --  PROGRAMMERS: Ben Barbour, Kara Martens
 --
 --  REVISIONS (date and description):
 --
 --  DATE: 2010-01-23
 --
 --  NOTES: Singleton - retrieve reference through CommClient::Instance()
 ----------------------------------------------------------------------------------------------------------*/

#include "Commclient.h"

using std::string;

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::CommClient
 --
 -- DATE: 2010-01-23
 --
 -- NOTES: Private constructor that should only be called once.
 ----------------------------------------------------------------------------------------------------------*/
CommClient::CommClient():isConnected_(false)
{
	sem_init(&semTCP_, 0, 1);
	sem_init(&semUDP_, 0, 1);
	tcpClient_ = 0;
	udpConnection_ = 0;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::Instance
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: A pointer to the CommClient Singleton.
 ----------------------------------------------------------------------------------------------------------*/
CommClient* CommClient::Instance()
{
    static CommClient* instance_ =0;

    if (!instance_)
        instance_ = new CommClient();
    return instance_;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::connect
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --  string name:    the player name
 --  string address: the address of the server, in dotted decimal format
 --
 -- RETURN: If connection was successful: your clientID (always >= 0).
 --         If server could not be found: -1
 --         If that name is in use: -2
 --         If other network error: -3
 ----------------------------------------------------------------------------------------------------------*/
int CommClient::connect(const string name, const string address, const string port, const string ship)
{
	ServerMessage sm;

    if (!isConnected_)
    {
    	tcpClient_ = new TCPClient();

        if (!tcpClient_->Connect(address, port))
        	return -1;
        isConnected_ = true;
        string msg = name + "," + ship;
        sm = tcpClient_->Login(msg);

        if (sm.GetData() == "FULL")
        	return -2;
        else if (sm.GetClientID() == MAX_CLIENTS + 1)
        	return -2;

        tcpClient_->setClientId(sm.GetClientID());
        tcpClient_->StartRdThread(&serverMsgs_, &semTCP_);

        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(UDP_PORT_SERV);
        if (inet_pton(AF_INET, address.c_str(), &servAddr.sin_addr) != 1)
            Logger::LogNQuit("Error connection client - bad IP");
        udpConnection_ = new UDPConnection(UDP_PORT_CLI);
        pthread_create(&readThread_, NULL, CommClient::readThreadUDP, NULL);
        return sm.GetClientID();
    }
    return -1;
}
/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::nextUpdate
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: the update object the front of the queue
 --
 -- NOTES: Always call CommClient::hasNextUpdate before calling this function.
 ----------------------------------------------------------------------------------------------------------*/
UpdateObject CommClient::nextUpdate()
{
	sem_wait(&semUDP_);
    UpdateObject update = updates_.front();
    updates_.pop();
    sem_post(&semUDP_);
    return update;
}
/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::nextServerMessage
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: the ServerMessage at the front of the queue
 --
 -- NOTES: Always call CommClient::hasNextServerMessage before calling this function.
 ----------------------------------------------------------------------------------------------------------*/
ServerMessage CommClient::nextServerMessage()
{
	sem_wait(&semTCP_);
    ServerMessage serverMsg = serverMsgs_.front();
    serverMsgs_.pop();
    sem_post(&semTCP_);
    return serverMsg;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::disconnect
 --
 -- DATE: 2010-01-23
 --
 -- NOTES: Informs the server of disconnection, then disconnects from the server gracefully.
 ----------------------------------------------------------------------------------------------------------*/
void CommClient::disconnect()
{
    if (isConnected_)
    {
    	sem_wait(&semTCP_);
    	while (!serverMsgs_.empty())
    		serverMsgs_.pop();
    	sem_post(&semTCP_);
    	tcpClient_->Logout();
    	isConnected_ = false;
        if (tcpClient_)
        	delete tcpClient_;
        if (udpConnection_)
        	delete udpConnection_;
        tcpClient_ = 0;
        udpConnection_ = 0;
    }
    else
    {
    	Logger::LogNContinue("CommClient::disconnect - Already disconnected");
    }
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::sendServerMsg
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
        Logger::LogNContinue("CommClient::sendServerMsg - Not connected");
}
/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::hasNextUpdate
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: if there is another update available in the queue
 ----------------------------------------------------------------------------------------------------------*/
bool CommClient::hasNextUpdate()
{
	bool result;
	sem_wait(&semUDP_);
	result = !updates_.empty();
	sem_post(&semUDP_);
	return result;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::hasNextServerMessage
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: is there is another server message available in the queue
 ----------------------------------------------------------------------------------------------------------*/
bool CommClient::hasNextServerMessage()
{
	bool result;
	sem_wait(&semTCP_);
	result = !serverMsgs_.empty();
	sem_post(&semTCP_);
	return result;
}
/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::sendAction
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --  ClientAction action:    the action to send to the server (should send one every frame)
 ----------------------------------------------------------------------------------------------------------*/
void CommClient::sendAction(ClientAction action)
{
	BYTE* buffer = 0;
	if (isConnected_)
	{
		action.serialise(&buffer);
		udpConnection_->sendMessage((sockaddr*)&this->servAddr, buffer, ClientAction::serialiseSize);
		free(buffer);
	}
	else
	{
		Logger::LogNContinue("CommClient::sendAction - Could Not Send ClientAction");
	}
}
/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: CommClient::readThreadUDP
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --		void* args: is ignored, should be NULL
 --
 -- RETURN: NULL
 ----------------------------------------------------------------------------------------------------------*/
void* CommClient::readThreadUDP(void*)
{
	while(true)
	{
		BYTE* buffer;
		ssize_t size = CommClient::Instance()->udpConnection_->recvMessage(&buffer);
		if(size < 0)
			break;
		if (size == UpdateObject::serializeSize)
		{
			UpdateObject update(buffer);
			free(buffer);
			sem_wait(&CommClient::Instance()->semUDP_);
			CommClient::Instance()->updates_.push(update);
			sem_post(&CommClient::Instance()->semUDP_);
		}
		else
		{
			Logger::LogNContinue("Bad packet size received");
		}
	}

    return 0;
}
