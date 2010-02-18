#include "tcpclient.h"

using namespace std;

TCPClient::TCPClient()
{
    /*
     Get host by name

     Check hostent h_addrtype for AF_INET(ipv6)

     Convert IP for debugging info (inet_ntop)

     Create Socket (socket(PF_INET, SOCK_STREAM, IPPROTO_IP)

     Set port (sockaddr.sin_port = htons(port)

     Copy h_addrlist[x] to sockaddr struct, where x is desired host IP

     Set sockaddr.sin_family to AF_INET

     Connect! (connect(int sock, sa, sizeof(sa))

     END CONNECT PHASE

     Read Client ID

     Read Scoreboard / Player names

     While (!done)

       Read Message/Write (Threaded, Async, or MP?)

       If logout

         SendServMsg(LOG_OUT)

         GOTO EXIT

       If Shutdown

         GOTO EXIT

       If EOF

         Notify Game lost connection

         GOTO EXIT

      EXIT PHASE

      close(socket)

      */
}

int TCPClient::Login(string ip, int port)
{
    return 0;
}
