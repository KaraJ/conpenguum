#include "udpClient.h"

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: UDPClient
--
-- DATE: 2010-02-18
--
-- INTERFACE:
--		char* addr:	the IP address of the server
--
----------------------------------------------------------------------------------------------------------*/
UDPClient::UDPClient(const char* addr)
{
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(UDP_PORT);
    if(inet_pton(AF_INET, addr, &servaddr.sin_addr) != 1)
    	perror("error converting IP address");

	this->sockfd_ = SocketWrapper::Socket(AF_INET, SOCK_DGRAM, 0);
}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: sendMessage
--
-- DATE: 2010-02-18
--
-- INTERFACE:
--		const void* data:	the data to send
--		size_t datalen:		the length of the data
--
-- RETURN: void
--
-- NOTES: Error handling is done in Sendto
----------------------------------------------------------------------------------------------------------*/
void UDPClient::sendMessage(const void* data, size_t dataLen)
{
	SocketWrapper::Sendto(this->sockfd_, data, dataLen, 0, (struct sockaddr*)&servaddr, sizeof(struct sockaddr));
}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: recvMessage
--
-- DATE: 2010-02-18
--
-- INTERFACE:
--		void* buff:	The buffer to put the data into
--
-- RETURN: void
--
-- NOTES: Used for debugging, receiving will be in a seperate thead later.
----------------------------------------------------------------------------------------------------------*/
void UDPClient::recvMessage(void * buff)
{
	int n;
	n = SocketWrapper::Recvfrom(this->sockfd_, buff, 1024, 0, 0, 0);
	((char *)buff)[n] = '\0';
}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: ~UDPClient
--
-- DATE: 2010-02-18
--
-- NOTES: Close the File descriptor for the socket.
----------------------------------------------------------------------------------------------------------*/
UDPClient::~UDPClient()
{
	close(this->sockfd_);
}
