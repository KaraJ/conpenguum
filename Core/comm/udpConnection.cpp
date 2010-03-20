/*----------------------------------------------------------------------------------------------------------
--  SOURCE FILE: udpConnection.cpp
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

#include "udpConnection.h"

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: UDPConnection
--
-- DATE: 2010-02-18
--
-- INTERFACE:
--
-- RETURN:
----------------------------------------------------------------------------------------------------------*/
UDPConnection::UDPConnection()
{
    struct sockaddr_in servaddr;

    this->sockfd_ = SocketWrapper::Socket(AF_INET, SOCK_DGRAM, 0);

    // set up the address structure
    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(UDP_PORT);
    
    //We can remove this if we used different ports for client and server
    SocketWrapper::Bind(this->sockfd_, &servaddr, sizeof(sockaddr_in));
}

UDPConnection::~UDPConnection()
{
	close(sockfd_);
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
void UDPConnection::sendMessage(struct sockaddr* to, const void* data, size_t dataLen)
{
	BYTE* buffer = (BYTE*)malloc(sizeof(BYTE) * (dataLen + 1));
	memcpy(buffer, data, dataLen);
	buffer[dataLen] = CRC::makeCRC((BYTE*)data, dataLen);
	SocketWrapper::Sendto(this->sockfd_, buffer, dataLen + 1, 0, to, sizeof(struct sockaddr));
	free(buffer);
}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: recvMessage
--
-- DATE: 2010-02-25
--
-- INTERFACE:
--      BYTE** buffer:      Should be null when passed in. Will be filled with the incoming data.
--      size_t* bufSize:    The amount of data in buffer.
--
-- RETURN: -1 on error. -2 on bad CRC
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/
ssize_t UDPConnection::recvMessage(BYTE** buffer)
{
    sockaddr_in from;
    socklen_t socklen;
    (*buffer) = (BYTE*)malloc(UDP_MAXMSG * sizeof(BYTE));
    ssize_t len = SocketWrapper::Recvfrom(this->sockfd_, *buffer, UDP_MAXMSG, NULL, (sockaddr*)&from, &socklen);
    if (len == -1)
    	return -1;
    if (!CRC::checkCRC((*buffer), len))
    	return -2;
    return len - 1;
}
