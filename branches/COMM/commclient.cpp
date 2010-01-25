/*----------------------------------------------------------------------------------------------------------
--  SOURCE FILE: commclient.cpp
--
--  PROGRAM: TuxSpace
--
--  METHODS:
--      bool connect(const string name, const string address)
--      void disconnect()
--      void sendChat(const string msg, int toClientID)
--      void sendServerMsg(const string msg)
--      void sendAction(const ClientAction action)
--
--  PROGRAMMER: Ben Barbour
--
--  REVISIONS (date and description):
--
--  DATE: 2010-01-23
--
--  NOTES: Singleton - retrieve reference through CommClient::Instance()
----------------------------------------------------------------------------------------------------------*/

#include "commclient.h"

CommClient* CommClient::Instance()
{
    static CommClient* theClient;
    if (!theClient)
        theClient = new CommClient();
    return theClient;
}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: connect
--
-- DATE: 2010-01-23
--
-- INTERFACE:
--  string name:    the player name
--  string address: the address of the server, in dotted decimal format
--
-- RETURN: If connection was succesfull: your clientID (always > 0).
--         If server could not be found: -1
--         If that name is in use: -2
--         If other network error: -3
----------------------------------------------------------------------------------------------------------*/
int connect(const string name, const string address)
{
    return -1;
}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: disconnect
--
-- DATE: 2010-01-23
--
-- NOTES: Informs the server of disconnection, then disconnects from the server gracefully.
----------------------------------------------------------------------------------------------------------*/
void disconnect()
{

}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: sendChat
--
-- DATE: 2010-01-23
--
-- INTERFACE:
--  string msg:     the message to send
--  int toClientID: the clientID (or teamID, in a team match) to send to
----------------------------------------------------------------------------------------------------------*/
void sendChat(const string msg, int id)
{

}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: sendServerMsg
--
-- DATE: 2010-01-23
--
-- INTERFACE:
--  string msg:     the message to send to send to the server
----------------------------------------------------------------------------------------------------------*/
void sendServerMsg(const string msg)
{

}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: sendAction
--
-- DATE: 2010-01-23
--
-- INTERFACE:
--  ClientAction action:    the action to send to the server (should send one every frame
----------------------------------------------------------------------------------------------------------*/
void sendAction(const ClientAction action)
{

}