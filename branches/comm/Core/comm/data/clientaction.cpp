/*----------------------------------------------------------------------------------------------------------
--  SOURCE FILE: clientAction.h
--
--  PROGRAM: TuxSpace
--
--  CONSTRUCTORS:
--      ClientAction(int clientID, int type)
--  METHODS:
--      void serialise(BYTE* buffer, size_t& buffSize)
--
--  PROGRAMMER: Ben Barbour
--
--  REVISIONS (date and description):
--
--  DATE: 2010-02-18
--
-- NOTES:
--  bits    value           bits    value
--  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--  0-4    clientID         5-8     actionBitMask
--
----------------------------------------------------------------------------------------------------------*/

#include "clientaction.h"

using std::ostream;
using std::endl;

ClientAction::ClientAction(BYTE* buffer)
{
    clientID_ = buffer[0] >> 3;
    BYTE tmp = ((buffer[0] << 1) & 0x0F) | (buffer[1] >> 7);
    mask_.setBitField(tmp);
}

void ClientAction::serialize(BYTE** buffer) const
{
    BYTE tmp;
    (*buffer) = new BYTE[serializeSize];
    memset((*buffer), 0, serializeSize);

    tmp = mask_.getBitField() & 0x0F;
    (*buffer)[0] = clientID_ << 3;
    (*buffer)[0] |= tmp >> 1;
    (*buffer)[1] = tmp << 7;
}

void ClientAction::print(ostream& out)
{
    out << "Client ID:    " << clientID_ << endl;
    out << "Firing:       " << isFiring() << endl;
    out << "Left:         " << isTurningLeft() << endl;
    out << "Right:        " << isTurningRight() << endl;
    out << "Accelerating: " << isAccelerating() << endl;
}
