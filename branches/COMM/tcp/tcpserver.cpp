#include "tcpserver.h"
#include <iostream>
#include <pthread.h>

int TCPServer::numConnected = 0;

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

void* ConnectThread(void *ptr)
{
    char buffer[BUFFSIZE];
    int received = -1;
    int sock = *((int*) ptr);    

    TCPServer::numConnected++;
    /* Receive message */
    if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0)
    {
        TCPServer::Die("Failed to receive initial bytes from client");
    }
    printf("[%d]Received: %s\n", sock, buffer);
    /* Send bytes and check for more incoming data in loop */
    while (received > 0)
    {
        /* Send back received data */
        if (send(sock, buffer, received, 0) != received)
        {
            TCPServer::Die("Failed to send bytes to client");
        }
        memset(buffer, 0, BUFFSIZE);
        /* Check for more data */
        if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0)
        {
            TCPServer::Die("Failed to receive additional bytes from client");
        }
        printf("[%d]Received: %s\n", sock, buffer);
        fflush(stdout);
    }
    fprintf(stdout, "Client disconnected[Socket: %d, Connected: %d]\n",
                sock, (TCPServer::numConnected - 1));
    close(sock);
    TCPServer::numConnected--;
    return NULL;
}

void TCPServer::run()
{
    int clientsock;
    struct sockaddr_in echoclient;

    /* Listen on the server socket */
    if (listen(serversock, MAXPENDING) < 0)
    {
        Die("Failed to listen on server socket");
    }
    std::cout << "Listening for connections.\n";

    /* Run until cancelled */
    while (1)
    {
        unsigned int clientlen = sizeof (echoclient);
        /* Wait for client connection */
        if ((clientsock = accept(serversock, (struct sockaddr *) & echoclient, &clientlen)) < 0)
            Die("Failed to accept client connection");

        fprintf(stdout, "Client connected[Socket: %d, Connected: %d]: %s\n",
                clientsock, (numConnected + 1), inet_ntoa(echoclient.sin_addr));
        /*HandleClient(clientsock);*/
        pthread_t thread;
        pthread_create(&thread, NULL, ConnectThread, &clientsock);
    }
}
