#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

/* Wrappers for common Socket operations. Leaving as static methods */
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>

class SocketWrapper
{
public:
    static int  Socket  (int family, int type, int protocol);
    static void Bind    (int fd, const struct sockaddr *sa, socklen_t salen);
    static int  Accept  (int fd, struct sockaddr *sa, socklen_t *salenptr);
    static void Connect (int fd, const struct sockaddr *sa, socklen_t salen);
    static void Listen  (int fd, int backlog);
    static void Write   (int fd, const void *vptr, size_t n);
    static void Recvfrom(int fd, const void* buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t addrlen);
    static void Sendto	(int fd, const void*buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen);

private:
    SocketWrapper() {}
};

#endif // SOCKETWRAPPER_H
