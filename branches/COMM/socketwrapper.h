#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

/* Wrappers for common Socket operations. Leaving as static methods */

class SocketWrapper
{
public:
    static int Socket(int family, int type, int protocol);
    static void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
    static int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
    static void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
    static void Listen(int fd, int backlog);
    static void Write(int fd, const void *vptr, size_t n);

private:
    SocketWrapper::SocketWrapper() {}
};

#endif // SOCKETWRAPPER_H
