/*----------------------------------------------------------------------------------------------------------
--  SOURCE FILE: commserver.cpp
--
--  PROGRAM: TuxSpace
--
--  METHODS:
--      void sendUpdate(const UpdateObject update);
--      void sendServerMsg(const string msg);
--
--  PROGRAMMER: Ben Barbour
--
--  REVISIONS (date and description):
--
--  DATE: 2010-01-23
--
--  NOTES: Singleton - retrieve reference through CommServer::Instance()
----------------------------------------------------------------------------------------------------------*/

#include "commserver.h"

using namespace std;

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: sendUpdate
--
-- DATE: 2010-01-23
--
-- INTERFACE:
--  UpdateObject update:    the UpdateObject to send
--  int* clientIDs:         a pointer to an array of clientID's to send the update to
--  int numClients:         the number of clients in clientIDs
----------------------------------------------------------------------------------------------------------*/
void sendUpdate(const UpdateObject update, const int* clientIDs, int numClients)
{

}

/*----------------------------------------------------------------------------------------------------------
-- FUNCTION: sendServerMsg
--
-- DATE: 2010-01-23
--
-- INTERFACE:
--  string msg:     the message to send
--  int* clientIDs: a pointer to an array of clientID's to send the message to. Use null to send to all.
--  int numClients: the number of clients in clientIDs. If clientIDs = null, this is ignored.
----------------------------------------------------------------------------------------------------------*/
void sendServerMsg(const string msg, const int* clientIDs, int numClients)
{

}
