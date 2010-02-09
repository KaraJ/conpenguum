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
	
	/*Message m(33, MT_LOGIN, "This is a test!");
    std::cout << m << std::endl;
    std::vector<BYTE> data = m.Serialize();
    for (size_t i = 0; i < data.size(); i++)
    {
        printf("%x ", data[i]);
    }
    Message m2(data);
    std::cout << std::endl << m2 << std::endl;*/

    s.Run();

    return (EXIT_SUCCESS);
}
