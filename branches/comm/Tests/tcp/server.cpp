#include <stdlib.h>
#include <iostream>
#include "tcpserver.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: server <port>\n");
        exit(1);
    }

    TCPServer s(atoi(argv[1]));

    s.run();

    return (EXIT_SUCCESS);
}