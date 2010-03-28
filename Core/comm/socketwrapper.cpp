#include "socketwrapper.h"
#include <fcntl.h>
using namespace std;

int SocketWrapper::Socket(int family, int type, int protocol)
{
    int n;

    if ( (n = socket(family, type, protocol)) < 0)
        Logger::LogNQuit("Socket error.");

    return (n);
}

void SocketWrapper::Bind(int fd, const struct sockaddr_in *sa, socklen_t salen)
{
    if (bind(fd, (sockaddr*)sa, salen) < 0)
        Logger::LogNQuit("Bind error.");
}

int SocketWrapper::Accept(int fd, sockaddr_in *sa, socklen_t *salenptr)
{
    int n;

    if ( (n = accept(fd, (sockaddr*)sa, salenptr)) < 0)
        Logger::LogNQuit("Accept error.");

    return(n);
}

bool SocketWrapper::Connect(int fd, const struct sockaddr_in *sa, socklen_t salen)
{
	struct timeval tv;
	fd_set connSet;
	socklen_t tmp;
	int err;
	bool result;

	ToggleNonBlock(fd, true);
	if (connect(fd, (sockaddr*)sa, salen) != -1)
	{
		result = true;
	}
	else if (errno == EINPROGRESS) //Delayed connect
	{
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		FD_ZERO(&connSet);
		FD_SET(fd, &connSet);
		if (select(fd + 1, NULL, &connSet, NULL, &tv) > 0) //Wait 5 seconds
		{
			tmp = sizeof(int);
			getsockopt(fd, SOL_SOCKET, SO_ERROR, (void*)(&err), &tmp); //Check if we connected
			result = !err;
		}
	}
	ToggleNonBlock(fd, false);
	return result;
}

void SocketWrapper::Listen(int fd, int backlog)
{
    if (listen(fd, backlog) < 0)
        Logger::LogNQuit("Listen error.");
}

bool SocketWrapper::Write(int sock, const void *vptr, size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;
    char* buff = (char*) vptr;

    while (nleft > 0)
    {
        if ( (nwritten = write(sock, buff, nleft)) <= 0)
		{
        	Logger::LogNContinue("Write error");
        	return false;
		}

        nleft -= nwritten;
        buff  += nwritten;
    }
    return true;
}

//TODO: Check all calls to this to make sure they're checking the return values
bool SocketWrapper::Read(int sock, void *vptr, size_t size)
{
	size_t  nleft = size;
	ssize_t nread;
	char* buff = (char*) vptr;

	while (nleft > 0)
	{
		if ( (nread = read(sock, buff, nleft)) < 0)
		{
			perror("read()");
			Logger::LogNContinue("Read error");
			return false;
		}
		if (nread == 0)
			return false;

		nleft -= nread;
		buff  += nread;
	}
	return true;
}

ssize_t SocketWrapper::Recvfrom(int fd, void* buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t* addrlen)
{
	ssize_t retval;

	if((retval = recvfrom(fd, (void*)buff, nbytes, flags, from, addrlen)) < 0)
	{
		Logger::LogNContinue("Recvfrom error");
	}

	return retval;
}

ssize_t SocketWrapper::Sendto(int fd, const void* buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen)
{
	ssize_t retval;

	if((retval = sendto(fd, buff, nbytes, flags, to, addrlen)) == -1)
        Logger::LogNContinue("Sendto error");

	return retval;
}

void SocketWrapper::ToggleNonBlock(int fd, bool toggleOn)
{
	int ctls;
	if (toggleOn)
	{
		ctls = fcntl(fd, F_GETFL, NULL); //Set socket non-blocking
		ctls |= O_NONBLOCK;
		ctls = fcntl(fd, F_SETFL, ctls);
	}
	else
	{
		ctls = fcntl(fd, F_GETFL, NULL); //Set to blocking
		ctls &= (~O_NONBLOCK);
		ctls = fcntl(fd, F_SETFL, ctls);
	}
}
