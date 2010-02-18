#include "socketwrapper.h"

using namespace std;

int SocketWrapper::Socket(int family, int type, int protocol)
{
    int n;

    if ( (n = socket(family, type, protocol)) < 0)
        cerr << "Socket error" << endl;

    return (n);
}

void SocketWrapper::Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
        cerr << "Bind error" << endl;
}

int SocketWrapper::Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;

    if ( (n = accept(fd, sa, salenptr)) < 0)
		cerr << "Accept error" << endl;

    return(n);
}

void SocketWrapper::Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (connect(fd, sa, salen) < 0)
        cerr << "Connect error" << endl;
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
            /*if (nwritten < 0 && errno == EINTR)
                nwritten = 0; /* and call write() again
            else*/
			cerr << "write error" << endl; /* error */
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }
}

int SocketWrapper::Read(int fd, void *vptr, size_t n)
{
	ssize_t nread;

	if ( (nread = read(fd, vptr, n)) <= 0)
	{
		/*if (nwritten < 0 && errno == EINTR)
			nwritten = 0; /* and call write() again
		else*/
		cerr << "Read error" << endl; /* error */
	}

	return nread;
}

ssize_t SocketWrapper::Recvfrom(int fd, void* buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t addrlen)
{
	ssize_t retval;

	if((retval = recvfrom(fd, (void*)buff, nbytes, flags, from, &addrlen)) < 0)
		cerr << "Recvfrom error" << endl;

	return retval;
}

ssize_t SocketWrapper::Sendto(int fd, const void* buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen)
{
	ssize_t retval;

	if((retval = sendto(fd, buff, nbytes, flags, to, addrlen)) == -1)
		cerr << "Sendto error" << endl;

	return retval;
}

