#include "udpClient.h"

bool connected;

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

	sockfd_ = SocketWrapper::Socket(AF_INET, SOCK_DGRAM, 0);
	connected = true;

	pthread_create(&readThread, NULL, ReadThread, &sockfd_);
}

void* ReadThread(void* args)
{
	int* sockfd = (int*)args;
	BYTE buffer[MAXUDP];
	UpdateObject* update;
	int numRead;
	while(1)
	{
		numRead = SocketWrapper::Recvfrom(*sockfd, buffer, MAXUDP, 0, 0, 0);
		if(numRead == -1)
			break;
		update = new UpdateObject(buffer, numRead);
		CommClient::Instance()->addUpdate(*update);
	}

	return 0;
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
void UDPClient::sendMessage(const BYTE* data, size_t dataLen)
{
	BYTE* buffer = (BYTE*)malloc(sizeof(BYTE) * (dataLen + 1));
	memcpy(buffer, data, dataLen);
	buffer[dataLen] = CRC::makeCRC(data, dataLen);
	SocketWrapper::Sendto(this->sockfd_, buffer, dataLen+1, 0, (struct sockaddr*)&servaddr, sizeof(struct sockaddr));
	free(buffer);
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
-- NOTES: Used for debugging, receiving will be in a separate thread later.
----------------------------------------------------------------------------------------------------------*/
void UDPClient::recvMessage(BYTE * buff)
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
	pthread_join(readThread, 0);
}
