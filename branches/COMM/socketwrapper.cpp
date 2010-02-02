#include "socketwrapper.h"



int SocketWrapper::Socket(int family, int type, int protocol)
{
    int n;

    if ( (n = socket(family, type, protocol)) < 0)
        fprintf(stderr, "socket error");

    return (n);
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
        fprintf(stderr, "bind error");
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;

    while (1)
    {
        if ( (n = accept(fd, sa, salenptr)) < 0)
        {
            if (errno == ECONNABORTED)
                continue;
            fprintf(stderr, "accept error");
            break;
        }
    }
    return(n);
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (connect(fd, sa, salen) < 0)
        fprintf(stderr, "connect error");
}

void Listen(int fd, int backlog)
{
    char *ptr;

    /* can override 2nd argument with environment variable */
    if ( (ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if (listen(fd, backlog) < 0)
        fprinf(stderr, "listen error");
}

void Write(int fd, const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0; /* and call write() again */
            else
                fprintf(stderr, "write error"); /* error */
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }

    return(n);
}
/* end writen */
