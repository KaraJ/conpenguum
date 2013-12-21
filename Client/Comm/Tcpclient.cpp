#include "Tcpclient.h"
#include "unistd.h"

using std::queue;
using std::string;

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: TCPClient::SendMessage
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: void
 --
 -- NOTES: Call this function to send a chat message to other players.
 ----------------------------------------------------------------------------------------------------------*/
void TCPClient::SendMessage(string message)
{
	ServerMessage msgBuff;
	msgBuff.SetClientID(clientId_);
	msgBuff.SetData(message);
	msgBuff.SetMsgType(ServerMessage::MT_CHAT);
	TCPConnection::WriteMessage(tcpSocket_, msgBuff);
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: TCPClient::ReadThread
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: void
 --
 -- NOTES: Main read thread function, read messages sent over TCP and push into queue.
 ----------------------------------------------------------------------------------------------------------*/
void* TCPClient::ReadThread(void* param)
{
	TCPClient* tcpClient = (TCPClient*)param;
	ServerMessage incomingMsg;
	while (tcpClient->connected_)
	{
		if(!TCPConnection::ReadMessage(tcpClient->tcpSocket_, &incomingMsg))
		{
			tcpClient->Logout();
			ServerMessage shutdown;
			shutdown.SetMsgType(ServerMessage::MT_SHUTDOWN);
			sem_wait(tcpClient->semSM_);
			tcpClient->msgBuff_->push(shutdown);
			sem_post(tcpClient->semSM_);
			break;
		}
		sem_wait(tcpClient->semSM_);
		tcpClient->msgBuff_->push(incomingMsg);
		sem_post(tcpClient->semSM_);
	}
	return 0;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: TCPClient::StartRdThread
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: void
 --
 -- NOTES: Read thread creation wrapper, passes the Tcpclient as a parameter to the read thread.
 ----------------------------------------------------------------------------------------------------------*/
void TCPClient::StartRdThread(queue<ServerMessage> *msgBuff, sem_t *semSM)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	msgBuff_ = msgBuff;
	semSM_ = semSM;

	if (pthread_create(&rThread_, &attr, TCPClient::ReadThread, this))
		Logger::LogNQuit("TCPClient: Unable to start read thread.");
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: TCPClient::Connect
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: true on success, false otherwise
 --
 -- NOTES: Call this function to attempt to connect via TCP to the specified IP on the specified port.
 ----------------------------------------------------------------------------------------------------------*/
bool TCPClient::Connect(const string& ip, const string& port)
{
	struct addrinfo  hints;
    struct addrinfo  *servList, *p;
    int gaiErr;
    bool result = false;

	bzero(&hints, sizeof(hints));
	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	gaiErr = getaddrinfo(ip.c_str(), port.c_str(), &hints, &servList);

	if (servList == 0)
		Logger::LogNQuit(gai_strerror(gaiErr));

	for (p = servList; p != NULL; p = p->ai_next)
	{
		tcpSocket_ = SocketWrapper::Socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		if (SocketWrapper::Connect(tcpSocket_, (sockaddr_in*)p->ai_addr, p->ai_addrlen))
		{
			result = true;
			break; /* Success */
		}

		close(tcpSocket_);
	}

	if (p == NULL)
		Logger::LogNContinue("TCPClient: Unable to connect to server.");

	connected_ = true;
	freeaddrinfo(servList);

	return result;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: TCPClient::Login
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: ServerMessage: The Init message containing your new clientId.
 --
 -- NOTES: Remember to check the returned clientId, if it is > MAX_CLIENTS, an error has occurred.
 ----------------------------------------------------------------------------------------------------------*/
ServerMessage TCPClient::Login(string playerName)
{
	ServerMessage msg;

	msg.SetClientID(MAX_CLIENTS + 1);
	msg.SetMsgType(ServerMessage::MT_LOGIN);
	msg.SetData(playerName);

	TCPConnection::WriteMessage(tcpSocket_, msg); //Send login message to server

	TCPConnection::ReadMessage(tcpSocket_, &msg);
	if (msg.GetMsgType() != ServerMessage::MT_INIT)
	{
		Logger::LogNContinue("Expecting INIT message but received:");
		msg.SetClientID(MAX_CLIENTS + 1);
	}

	return msg;
}

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: TCPClient::Logout
 --
 -- DATE: 2010-01-23
 --
 -- RETURN: void
 --
 -- NOTES: Call this function to close an established TCP connection.
 ----------------------------------------------------------------------------------------------------------*/
void TCPClient::Logout()
{
	connected_ = false;
	close(tcpSocket_);
}
