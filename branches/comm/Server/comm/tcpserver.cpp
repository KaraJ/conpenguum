#include "tcpserver.h"
#include <assert.h>

int TCPServer::connections = 0;

TCPServer::TCPServer(int _maxClients, int _timeOut)
    : maxClients(_maxClients), timeOut(_timeOut)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    assert(maxClients > 0);
    assert(timeout > 0);
    port = qrand() % 7000 + 1000;
}

TCPServer::TCPServer()
    : maxClients(10), timeOut(60000)
{
}

void TCPServer::run()
{
    /*
      serverSocket = CreateSocket

      Set up address structure

      Bind Address to socket

      Listen for connections

      While server is running

            newSocket = accept(new connection)

            pthread_t newThread

            pthread_create(newThread, NULL, ClientConnectThread, (void *)newSocket)

      //end while

      */
}

void* TCPServer::ClientConnectThread(void *ptr)
{
    int *socket = (int *)ptr;

    /* Initiate connection with client

       if connected >= maxClients
            send some error message
            exit

       connected++;

       get map info from engine / gameplay

       send map info to client

       get player / score info from engine / gameplay

       send player info

       wait for ack

       add player to queue of updating players

       while true

            if msg to send from server
                bytes = data.serialize()
                send bytes

            else if data read from client
                if msg = logout
                    alert engine / gameplay
                    break

                if msg = chat
                    send to engine / gameplay

        //end while
        connected--;
       */
}

bool TCPServer::HasMessages()
{
    bool msg = false;
    //Critical section
    msg = (cMsgList.size() > 0 || sMsgList.size() > 0);
    //end critical section
    return msg;
}

Message TCPServer::GetMessage()
{
    if (!HasMessages())
        return NULL;
    //critical section
    if (sMsgList.size() > 0)
    {
        Message next = sMsgList.front();
        sMsgList.pop();
        //end crit section
        return next;
    }
    Message next = cMsgList.front();
    sMsgList.pop();
    //end crit section
    return next;
}

void TCPServer::SendMessage(Message msg)
{
    //Match client id to thread somehow - probably magic

    //pass byte array from msg.Serialize()
}
