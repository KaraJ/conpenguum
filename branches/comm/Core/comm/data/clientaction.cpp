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
--  bits    value       bits    value
--  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--  0-4    clientID     5-8     actionBitMask
--
----------------------------------------------------------------------------------------------------------*/

#include "clientaction.h"

using std::ostream;
using std::endl;

ClientAction::ClientAction(BYTE* buffer, size_t buffSize)
{
    memcpy(this, buffer, buffSize);

    /*clientID_ = buffer[0] >> 4;
    mask_.setBitField(buffer[0] & 0x0F);*/
}

void ClientAction::serialize(BYTE** buffer, size_t& buffSize)
{
    buffSize = sizeof(*this);
    (*buffer) = new BYTE[buffSize];
    memcpy((*buffer), this, buffSize);

    /*BYTE tmp;
    buffSize = 2;
    (*buffer) = new BYTE[2];
    memset((*buffer), 0, buffSize);

    tmp = mask_.getBitField() & 0x0F;
    (*buffer)[0] = (clientID_ << 4) | tmp;*/
}
void ClientAction::print(ostream& out)
{
    out << "Client ID:    " << clientID_ << endl;
    out << "Firing:       " << isFiring() << endl;
    out << "Left:         " << isTurningLeft() << endl;
    out << "Right:        " << isTurningRight() << endl;
    out << "Firing:       " << isFiring() << endl;
    out << "Accelerating: " << isAccelerating() << endl;
}
