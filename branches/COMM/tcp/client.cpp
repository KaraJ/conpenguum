#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#include <iostream>

#define _REENTRANT
#define DCE_COMPAT
#define BUFFSIZE 32
#define TESTWORDS 8

std::string words[] = {"this ", "is ", "a ", "series ", "of ", "test ", "words", ".\n"};

void Die(std::string mess)
{
    perror(mess.c_str());
    exit(1);
}

void* listenThread(void*);

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in echoserver;
    unsigned int echolen;
    pthread_t listen;

    if (argc != 3)
    {
        fprintf(stderr, "USAGE: client <server_ip> <port>\n");
        exit(1);
    }
    /* Create the TCP socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        Die("Failed to create socket");
    }
    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof (echoserver)); /* Clear struct */
    echoserver.sin_family = AF_INET; /* Internet/IP */
    echoserver.sin_addr.s_addr = inet_addr(argv[1]); /* IP address */
    echoserver.sin_port = htons(atoi(argv[2])); /* server port */
    /* Establish connection */
    if (connect(sock,
            (struct sockaddr *) & echoserver,
            sizeof (echoserver)) < 0)
    {
        Die("Failed to connect with server");
    }
    /* Send the word to the server */
    pthread_create(&listen, NULL, listenThread, (void*) (&sock));
    for (size_t i = 0; i < TESTWORDS; i++)
    {
        echolen = words[i].length();
        if (send(sock, words[i].c_str(), echolen, 0) != echolen)
        {
            Die("Mismatch in number of sent bytes");
        }
        /* Receive the word back from the server */
        /*usleep(100);*/
        sleep(1);
    }
    close(sock);
    exit(0);

    return 0;
}

void *listenThread(void *ptr)
{
    int *sock = (int*) ptr;
    int received = 0;
    char buffer[BUFFSIZE];

    fprintf(stdout, "Received: ");
    do
    {
        int bytes = 0;
        if ((bytes = recv(*sock, buffer, BUFFSIZE - 1, 0)) < 1)
        {
            Die("Failed to receive bytes from server");
        }
        received += bytes;
        buffer[bytes] = '\0'; /* Assure null terminated string */
        fprintf(stdout, buffer);
        memset(buffer, 0, BUFFSIZE);
        fflush(stdout);
    }while (received > 0);    
    return NULL;
}
