#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

/* Wrappers for common Socket operations. Leaving as static methods */
#include <sys/socket.h>
#include <errno.h>
#include "../Logger.h"

class SocketWrapper
{
public:
    static int  	Socket  (int family, int type, int protocol);
    static void 	Bind    (int fd, const struct sockaddr *sa, socklen_t salen);
    static int  	Accept  (int fd, struct sockaddr *sa, socklen_t *salenptr);
    static void 	Connect (int fd, const struct sockaddr *sa, socklen_t salen);
    static void 	Listen  (int fd, int backlog);
    static void 	Write   (int fd, const void* vptr, size_t n);
    static int     Read    (int fd, void *vptr, size_t n);
    static ssize_t 	Recvfrom(int fd, void* buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t addrlen);
    static ssize_t 	Sendto	 (int fd, const void* buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen);

private:
    SocketWrapper() {}
};

#endif // SOCKETWRAPPER_H
