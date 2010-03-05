/*----------------------------------------------------------------------------------------------------------
--  SOURCE FILE: clientAction.h
--
--  PROGRAM: TuxSpace
--
--  CONSTRUCTORS:
--      ClientAction(int objectID)
--  METHODS:
--      void serialise(BYTE* buffer, size_t& buffSize)
--
--  PROGRAMMER: Ben Barbour
--
--  REVISIONS (date and description):
--
--  DATE: 2010-02-18
----------------------------------------------------------------------------------------------------------*/

#include "clientaction.h"

using std::ostream;
using std::endl;

/*----------------------------------------------------------------------------------------------------------
--  FUNCTION: ClientAction(int objectID)
--
--  INTERFACE:
--      ClientAction(int objectID)
--          objectID:   objIDs 0-31 are reserved for players. objIDs 32-155 can be used for bullets,
--                      explosions, robot unicorns, etc.
--
--  RETURNS: new ClientAction
----------------------------------------------------------------------------------------------------------*/
ClientAction::ClientAction(int objectID) : objID_(objID)
{

}

/*----------------------------------------------------------------------------------------------------------
--  FUNCTION: ClientAction(BYTE* buffer)
--
--  INTERFACE:
--      ClientAction(BYTE* buffer)
--          buffer: a byte array, should be the same one returned from a ClientAction::serialise() call or
--                  strangeness will occur.
--
--  RETURNS: new ClientAction
----------------------------------------------------------------------------------------------------------*/
ClientAction::ClientAction(BYTE* buffer)
{
    objID_ = buffer[0];
    mask_.setBitField(buffer[1]);
}

/*----------------------------------------------------------------------------------------------------------
--  FUNCTION: serialise(BYTE** buffer)
--
--  INTERFACE:
--      ClientAction(BYTE** buffer)
--          buffer: pointer to a byte array, will be filled with bytes that can be passed to the
--                  second constructor
--
--  NOTES:
--     Packet Structure
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- Byte    Bits
--         0    1   2   3   4   5   6   7
--  0      OID  OID OID OID OID OID OID OID
--         8    9   10  11  12  13  14  15
--  1      BM   BM  BM  BM  BM  BM  BM  BM
----------------------------------------------------------------------------------------------------------*/
void ClientAction::serialise(BYTE** buffer) const
{
    (*buffer) = new BYTE[serialiseSize];
    memset((*buffer), 0, serialiseSize);

    (*buffer)[0] = objID_;
    (*buffer)[1] = mask_.getBitField();
}

void ClientAction::print(ostream& out)
{
    out << "Object ID:    " << objID_ << endl;
    out << "Firing:       " << isFiring() << endl;
    out << "Left:         " << isTurningLeft() << endl;
    out << "Right:        " << isTurningRight() << endl;
    out << "Accelerating: " << isAccelerating() << endl;
    out << "Decelerating: " << isDecelerating() << endl;
}
