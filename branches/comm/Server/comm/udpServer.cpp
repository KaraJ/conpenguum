/*----------------------------------------------------------------------------------------------------------
--  SOURCE FILE: udpServer.cpp
--
--  PROGRAM: TuxSpace
--
--  METHODS:
--		UDPServer()
--		sendMessage(struct sockaddr* to, const void* data, size_t dataLen)
--		EchoMessage()
--
--  PROGRAMMER: Kara Martens
--
--  REVISIONS (date and description):
--
--  DATE: 2010-02-18
--
--  NOTES:
----------------------------------------------------------------------------------------------------------*/

#include "udpServer.h"
/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: UDPServer
--
-- DATE: 2010-02-18
--
-- INTERFACE:
--
-- RETURN:
----------------------------------------------------------------------------------------------------------*/
UDPServer::UDPServer()
{
    struct sockaddr_in servaddr;

    this->sockfd_ = SocketWrapper::Socket(AF_INET, SOCK_DGRAM, 0);

    // set up the address structure
    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(UDP_PORT);

    SocketWrapper::Bind(this->sockfd_, (struct sockaddr *)&servaddr, sizeof(sockaddr_in));
}
/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: sendMessage
--
-- DATE: 2010-02-18
--
-- INTERFACE:
--		struct sockaddr* to:	The address to send the data to
--		const void* data:		The data to send
--		size_t datalen:			The length of the data
--
-- RETURN: void
--
-- NOTES: The error handling is done in the Sendto function.
----------------------------------------------------------------------------------------------------------*/
void UDPServer::sendMessage(struct sockaddr* to, const void* data, size_t dataLen)
{
	SocketWrapper::Sendto(this->sockfd_, data, dataLen, 0, to, sizeof(struct sockaddr));
}
/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: EchoMessage
--
-- DATE: 2010-02-18
--
-- INTERFACE:
--
-- RETURN: void
--
-- NOTES: Used for testing to read a message and send it back to the client.
----------------------------------------------------------------------------------------------------------*/
void UDPServer::EchoMessage()
{
	int n;
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(sockaddr_in);
	char message[1024];

	n = SocketWrapper::Recvfrom(this->sockfd_, message, 1024, 0, (struct sockaddr*)&cliaddr, &len);
	SocketWrapper::Sendto(this->sockfd_, message, n, 0, (struct sockaddr*)&cliaddr, len);
}
