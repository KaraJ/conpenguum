#include "tcpclient.h"

using namespace std;

/*   TODO:

	 While (!done)

	 Read Message/Write (Threaded, Async, or MP?)

	 If logout

	 SendServMsg(LOG_OUT)

	 GOTO EXIT

	 If Shutdown

	 GOTO EXIT

	 If EOF

	 Notify Game lost connection

	 GOTO EXIT

	 EXIT PHASE

	 close(socket)

	 */

TCPClient::TCPClient() { }

void TCPClient::Connect(string& ip)
{
	struct addrinfo  hints;
    struct addrinfo  *servList, *p;
    int gaiErr;

	bzero(&hints, sizeof(hints));
	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	gaiErr = getaddrinfo(ip.c_str(), TCP_PORT, &hints, &servList);

	if (servList != 0)
		Logger::LogNQuit(gai_strerror(gaiErr));

	for (p = servList; p != NULL; p = p->ai_next)
	{
		tcpSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (tcpSocket == -1)
			continue;

		if (connect(tcpSocket, p->ai_addr, p->ai_addrlen) != -1)
			break; /* Success */

		close(tcpSocket);
	}

	if (p == NULL)
		Logger::LogNQuit("Unable to connect to server.");

	freeaddrinfo(servList);
}

int TCPClient::Login(string playerName)
{
	ServerMessage loginMsg;

	loginMsg.SetClientID(0);
	loginMsg.SetMsgType(ServerMessage::MT_LOGIN);
	loginMsg.SetData(playerName);

	TCPConnection::WriteMessage(tcpSocket, loginMsg);

	return 0;
}

TCPClient::~TCPClient()
{
	shutdown(tcpSocket, SHUT_RDWR);
}
