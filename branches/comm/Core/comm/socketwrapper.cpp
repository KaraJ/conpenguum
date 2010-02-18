#include "socketwrapper.h"

using namespace std;

int SocketWrapper::Socket(int family, int type, int protocol)
{
    int n;

    if ( (n = socket(family, type, protocol)) < 0)
        cerr << "socket error" << endl;

    return (n);
}

void SocketWrapper::Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
        cerr << "bind error" << endl;
}

int SocketWrapper::Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;

    while (1)
    {
        if ( (n = accept(fd, sa, salenptr)) < 0)
        {
            if (errno == ECONNABORTED)
                continue;
            cerr << "accept error" << endl;
            break;
        }
    }
    return(n);
}

void SocketWrapper::Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (connect(fd, sa, salen) < 0)
        cerr << "connect error" << endl;
}

void SocketWrapper::SocketWrapper::Listen(int fd, int backlog)
{
    char *ptr;

    /* can override 2nd argument with environment variable */
    if ( (ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if (listen(fd, backlog) < 0)
        cerr << "listen error" << endl;
}

void SocketWrapper::Write(int fd, const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = (char*) vptr;
    nleft = n;
    while (nleft > 0)
    {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0; /* and call write() again */
            else
                cerr << "write error" << endl; /* error */
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }
}

ssize_t Recvfrom(int fd, void* buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t addrlen)
{
	ssize_t retval;
	if((retval = recvfrom(fd, (void*)buff, nbytes, flags, from, &addrlen)) < 0)
	{
		cerr << "recvfrom error" << endl;
	}
	return retval;
}
ssize_t Sendto	(int fd, const void*buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen)
{
	ssize_t retval;
	if((retval = sendto(fd, buff, nbytes, flags, to, addrlen)) == -1)
	{
		cerr << "sendto error" << endl;
	}
	return retval;
}

