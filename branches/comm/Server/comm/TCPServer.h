#ifndef TCPSERVER_H_
#define TCPSERVER_H_

//System Includes
#include <netinet/in.h>

//User Includes
#include "comm/socketwrapper.h"
#include "comm/globals.h"

class TCPServer
{
public:
	void Init(std::string& ip);
	TCPServer() { }
	~TCPServer() { }
};

#endif /* TCPSERVER_H_ */
