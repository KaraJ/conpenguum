#include "Tcpclient.h"

using namespace std;

//Storage for class variables
queue<ServerMessage> *TCPClient::msgBuff_;
sem_t *TCPClient::semSM_;
bool TCPClient::connected_;

void TCPClient::SendMessage(string message)
{
	ServerMessage msgBuff;
	msgBuff.SetClientID(clientId_); //TODO: Why is this hard coded?
	msgBuff.SetData(message);
	msgBuff.SetMsgType(ServerMessage::MT_CHAT);
	TCPConnection::WriteMessage(tcpSocket, msgBuff);
}

void* TCPClient::ReadThread(void* param)
{
	int socket = *((int*)param);
	ServerMessage msgBuff;
	while (TCPClient::connected_)
	{
		TCPConnection::ReadMessage(socket, msgBuff);
		sem_wait(semSM_);
		msgBuff_->push(msgBuff);
		sem_post(semSM_);
	}
	return 0;
}

void TCPClient::StartRdThread(std::queue<ServerMessage> *msgBuff, sem_t *semSM)
{
	TCPClient::msgBuff_ = msgBuff;
	TCPClient::semSM_ = semSM;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	if (pthread_create(&rThread_, &attr, TCPClient::ReadThread, &tcpSocket))
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
		tcpSocket = SocketWrapper::Socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		if (SocketWrapper::Connect(tcpSocket, (sockaddr_in*)p->ai_addr, p->ai_addrlen) != -1)
		{
			result = true;
			break; /* Success */
		}

		close(tcpSocket);
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

	msgBuff.SetClientID(0);
	msgBuff.SetMsgType(ServerMessage::MT_LOGIN);
	msgBuff.SetData(playerName);

	TCPConnection::WriteMessage(tcpSocket, msgBuff); //Send login message to server
	TCPConnection::ReadMessage(tcpSocket, msgBuff); //Get init message from server

	return msgBuff;
}

void TCPClient::Logout()
{
	connected_ = false;
	shutdown(tcpSocket, SHUT_RDWR);
	close(tcpSocket);
}
