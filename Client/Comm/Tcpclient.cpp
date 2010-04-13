#include "Tcpclient.h"

using std::queue;
using std::string;

void TCPClient::SendMessage(string message)
{
	ServerMessage msgBuff;
	msgBuff.SetClientID(clientId_); //TODO: Why is this hard coded?
	msgBuff.SetData(message);
	msgBuff.SetMsgType(ServerMessage::MT_CHAT);
	TCPConnection::WriteMessage(tcpSocket_, msgBuff);
}

void* TCPClient::ReadThread(void* param)
{
	TCPClient* tcpClient = (TCPClient*)param;
	ServerMessage incomingMsg;
	while (tcpClient->connected_)
	{
		if(!TCPConnection::ReadMessage(tcpClient->tcpSocket_, incomingMsg))
		{
			tcpClient->Disconnect();
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
void TCPClient::Disconnect()
{
	close(tcpSocket_);
}
void TCPClient::StartRdThread(std::queue<ServerMessage> *msgBuff, sem_t *semSM)
{
	msgBuff_ = msgBuff;
	semSM_ = semSM;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	if (pthread_create(&rThread_, &attr, TCPClient::ReadThread, this))
		Logger::LogNQuit("TCPClient: Unable to start read thread.");
}

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

ServerMessage TCPClient::Login(string playerName)
{
	ServerMessage msgBuff;

	msgBuff.SetClientID(MAX_CLIENTS + 1);
	msgBuff.SetMsgType(ServerMessage::MT_LOGIN);
	msgBuff.SetData(playerName);

	TCPConnection::WriteMessage(tcpSocket_, msgBuff); //Send login message to server
	while (msgBuff.GetMsgType() != ServerMessage::MT_INIT)
	{
		TCPConnection::ReadMessage(tcpSocket_, msgBuff); //Get init message from server
		Logger::LogNContinue("Expecting INIT message but received:");
		Logger::LogNQuit(msgBuff.msgType);
	}

	return msgBuff;
}

void TCPClient::Logout()
{
	connected_ = false;
	shutdown(tcpSocket_, SHUT_RDWR);
	close(tcpSocket_);
}
