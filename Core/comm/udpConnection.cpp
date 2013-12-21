/*----------------------------------------------------------------------------------------------------------
--  SOURCE FILE: udpConnection.cpp
--
--  PROGRAM: TuxSpace
--
--  METHODS:
--		UDPConnection(int port)
--		~UDPConnection()
--		void sendMessage(struct sockaddr* to, const void* data, size_t dataLen)
--		ssize_t recvMessage(BYTE** buffer)
--
--  PROGRAMMER: Kara Martens
--
--  REVISIONS (date and description):
--
--  DATE: 2010-02-18
--
--  NOTES: UDPClient and UDPServer both have a UDPConnection for common functions.
----------------------------------------------------------------------------------------------------------*/

#include "udpConnection.h"
#include "unistd.h"

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: UDPConnection::UDPConnection
--
-- DATE: 2010-02-18
--
-- INTERFACE:
--		int port:	the UDP port
--
----------------------------------------------------------------------------------------------------------*/
UDPConnection::UDPConnection(int port)
{
    struct sockaddr_in servaddr;

    this->sockfd_ = SocketWrapper::Socket(AF_INET, SOCK_DGRAM, 0);

    // set up the address structure
    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    
    //We can remove this if we used different ports for client and server
    SocketWrapper::Bind(this->sockfd_, &servaddr, sizeof(sockaddr_in));
}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: UDPConnection::~UDPConnection
--
-- DATE: 2010-02-18
--
-- NOTES: Close the socket when the object is deleted.
----------------------------------------------------------------------------------------------------------*/
UDPConnection::~UDPConnection()
{
	close(sockfd_);
}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: UDPConnection::sendMessage
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
-- FUNCTION: UDPConnection::recvMessage
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
    socklen_t socklen = sizeof(from);
    (*buffer) = (BYTE*)malloc(UDP_MAXMSG * sizeof(BYTE));
    ssize_t len = SocketWrapper::Recvfrom(this->sockfd_, *buffer, UDP_MAXMSG, NULL, (sockaddr*)&from, &socklen);
    if (len == -1)
    	return -1;
    if (!CRC::checkCRC((*buffer), len))
    	return -2;
    return len - 1;
}
