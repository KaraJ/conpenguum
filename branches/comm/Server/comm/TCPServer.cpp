#include "TCPServer.h"

using namespace std;

void TCPServer::Init(const string port)
{
	istringstream iss(port);
	int tmp;
	iss >> tmp;

	tcpSocket_ = SocketWrapper::Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sa_ = {0};

	sa_.sin_family = AF_INET;
	sa_.sin_addr.s_addr = htonl(INADDR_ANY);
	sa_.sin_port = htons(tmp);

	SocketWrapper::Bind(tcpSocket_, &sa_, sizeof(sa_));
}

void TCPServer::StartListenThread()
{
	this->StartReadThread();
}

void TCPServer::StartReadThread()
{

}

void* TCPServer::ListenThread(void*)
{
	return 0;
}

void* TCPServer::ReadThread(void*)
{
	return 0;
}
