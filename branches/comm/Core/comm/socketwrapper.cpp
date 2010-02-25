#include "socketwrapper.h"

using namespace std;

int SocketWrapper::Socket(int family, int type, int protocol)
{
    int n;

    if ( (n = socket(family, type, protocol)) < 0)
        Logger::LogNQuit("Socket error.");

    return (n);
}

void SocketWrapper::Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
        Logger::LogNQuit("Bind error.");
}

int SocketWrapper::Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;

    if ( (n = accept(fd, sa, salenptr)) < 0)
        Logger::LogNQuit("Accept error.");

    return(n);
}

bool SocketWrapper::Connect(int fd, const struct sockaddr_in *sa, socklen_t salen)
{
    if (connect(fd, (sockaddr*)sa, salen) < 0)
    {
    	string buff = "Connect: Unable to connect to ";
    	buff += inet_ntoa(sa->sin_addr);
        Logger::LogNContinue("Connect: ");
        return false;
    }
    return true;
}

void SocketWrapper::Listen(int fd, int backlog)
{
    char *ptr;

    /* can override 2nd argument with environment variable */
    if ( (ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if (listen(fd, backlog) < 0)
        Logger::LogNQuit("Listen error.");
}

void SocketWrapper::Write(int sock, const void *buff, size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;

    while (nleft > 0)
    {
        if ( (nwritten = write(sock, buff, nleft)) <= 0)
            Logger::LogNQuit("Write error");

        nleft -= nwritten;
        buff  += nwritten;
    }
}

void SocketWrapper::Read(int sock, void *buff, size_t size)
{
	size_t  nleft = size;
	ssize_t nread;

	while (nleft > 0)
	{
		if ( (nread = read(sock, buff, nleft)) <= 0)
			Logger::LogNQuit("Read error");

		nleft -= nread;
		buff  += nread;
	}
}

ssize_t SocketWrapper::Recvfrom(int fd, void* buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t* addrlen)
{
	ssize_t retval;

	if((retval = recvfrom(fd, (void*)buff, nbytes, flags, from, addrlen)) < 0)
	{
		if(errno == EBADF)
			Logger::LogNContinue("Recvfrom Bad Descriptor");
		else
			Logger::LogNQuit("Recvfrom error");
	}

	return retval;
}

ssize_t SocketWrapper::Sendto(int fd, const void* buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen)
{
	ssize_t retval;

	if((retval = sendto(fd, buff, nbytes, flags, to, addrlen)) == -1)
        Logger::LogNQuit("Sendto error");

	return retval;
}

