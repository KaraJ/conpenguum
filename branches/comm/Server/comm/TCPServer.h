#ifndef TCPSERVER_H_
#define TCPSERVER_H_

//System Includes
#include <netinet/in.h>
#include <sstream>

//User Includes
#include "comm/socketwrapper.h"
#include "comm/globals.h"

class TCPServer
{
public:
	void Init(const std::string port);
	void StartListenThread();
	void StartReadThread();
	static void* ListenThread(void*);
	static void* ReadThread(void*);

private:
	int tcpSocket_;
};

#endif /* TCPSERVER_H_ */
