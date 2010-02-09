#include "tcpserver.h"
#include <iostream>
#include <pthread.h>
#include <sstream>
#include <time.h>
using namespace std;

int TCPServer::numConnected = 0;
long TCPServer::numMsgs = 0;

TCPServer::TCPServer(int port)
{

    /* Create the TCP socket */
    if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        Die("Failed to create socket");
    }
    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof (echoserver)); /* Clear struct */
    echoserver.sin_family = AF_INET; /* Internet/IP */
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY); /* Incoming addr */
    echoserver.sin_port = htons(port); /* server port */

    /* Bind the server socket */
    if (bind(serversock, (struct sockaddr *) & echoserver,
            sizeof (echoserver)) < 0)
    {
        Die("Failed to bind the server socket");
    }
    std::cout << "Server set up successfully.\n";
}

void* StatsThread(void*)
{
    time_t start = time(NULL);
    static long lastMsgs = 0;    
    while (1)
    {
        int msgs = (TCPServer::numMsgs - lastMsgs) / 5;
        lastMsgs = TCPServer::numMsgs;
        printf("Conn: %d Msgs: %d (", TCPServer::numConnected, TCPServer::numMsgs);
        cout << msgs << "/s) ";
        int secs = (time(NULL) - start), min = 0, hour = 0;
        cout << "Elapsed: ";
        if (secs >= 60)
        {
            min = secs / 60;
            secs %= 60;
        }
        if (min >= 60)
        {
            hour = min / 60;
            min %= 60;
        }
        if (hour)
            cout << hour << " hrs ";
        if (min)
            cout << min << " mins ";
        cout << secs << " secs" << endl;
        sleep(5);
    }

    return NULL;
}

void* ConnectThread(void *ptr)
{
    char buffer[BUFFSIZE] = {0};
    int received = -1;
    int sock = *((int*) ptr);

    TCPServer::numConnected++;
    /* Receive message */
    if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0)
    {
        TCPServer::Die("Failed to receive initial bytes from client");
    }
    Message msg(buffer);
    TCPServer::numMsgs++;
    //printf("-[%d]Received Message-\n", sock);
    //cout << msg << endl;
    /* Send bytes and check for more incoming data in loop */
    while (received > 0)
    {
        /* Send back received data */

        if (send(sock, msg.Serialize(), received, 0) != received)
        {
            TCPServer::Die("Failed to send bytes to client");
        }
        //printf("Sock: %d\n", sock);
        memset(buffer, 0, BUFFSIZE);
        /* Check for more data */
        if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0)        
        {
            //TCPServer::Die("Failed to receive additional bytes from client");
            cout << "Failed to receive additional bytes from client" << endl;
            break;
        }

        msg = Message(buffer);
        TCPServer::numMsgs++;
        //printf("-[%d]Received Message-\n", sock);
        //cout << msg << endl;
        fflush(stdout);
    }
    fprintf(stdout, "Client disconnected[Socket: %d, Connected: %d]\n",
            sock, (TCPServer::numConnected - 1));
    close(sock);
    TCPServer::numConnected--;
    return NULL;
}

void TCPServer::Run()
{
    int clientsock;
    struct sockaddr_in echoclient;

    /* Listen on the server socket */
    if (listen(serversock, MAXPENDING) < 0)
    {
        Die("Failed to listen on server socket");
    }
    std::cout << "Listening for connections.\n";
    pthread_t sthread;
    pthread_create(&sthread, NULL, StatsThread, NULL);

    /* Run until cancelled */
    if (fork() == 0)
    {
        char input[100];
        int id, type;
        while (scanf("%d %d %s", &id, &type, input))
        {
            std::string text(input);
            Message m(id, (MessageType) type, text);
            SendMesssage(m);
        }
    }
    else
    {
        while (1)
        {
            unsigned int clientlen = sizeof (echoclient);
            /* Wait for client connection */
            if ((clientsock = accept(serversock, (struct sockaddr *) & echoclient, &clientlen)) < 0)
                Die("Failed to accept client connection");

            fprintf(stdout, "Client connected[Socket: %d, Connected: %d]: %s\n",
                    clientsock, (numConnected + 1), inet_ntoa(echoclient.sin_addr));
            sockets.insert(std::pair<int, int*>(clientsock, &clientsock));
            //printf("sock: %d\n", (int) sockets.size());
            pthread_t thread;
            pthread_create(&thread, NULL, ConnectThread, &clientsock);
        }
    }
}

//work in progress, ignore for now

void TCPServer::SendMesssage(Message msg)
{
#if 0
    std::vector<BYTE> bData = msg.Serialize();
    int sent;
    char data[BUFFSIZE];
    for (size_t i = 0; i < bData.size(); i++)
        data[i] = bData[i];
    printf("ID: %d\n", sockets.size());
    // %d\n", (int)send(*sockets[msg.GetID()], data, BUFFSIZE, 0));
    /*if ((sent = send(*sockets[msg.GetID()], data, BUFFSIZE, 0)) <= 0)
    {
        printf("Sent: %d\n", sent);
        Die("Failed to send bytes to client");
    } */
#endif
}
