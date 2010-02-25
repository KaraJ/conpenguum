#include "tcpclient.h"

using namespace std;

void TCPClient::StartRdThread(std::queue<ServerMessage> *msgBuff, sem_t *semSM)
{
	msgBuff_ = msgBuff;
}

bool TCPClient::Connect(const string& ip)
{
	struct addrinfo  hints;
    struct addrinfo  *servList, *p;
    int gaiErr;
    bool result = false;

	bzero(&hints, sizeof(hints));
	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	gaiErr = getaddrinfo(ip.c_str(), TCP_PORT, &hints, &servList);

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
	shutdown(tcpSocket, SHUT_RDWR);
	close(tcpSocket);
}
