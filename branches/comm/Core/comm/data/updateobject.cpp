/*----------------------------------------------------------------------------------------------------------
 --  SOURCE FILE: clientAction.h
 --
 --  PROGRAM: TuxSpace
 --
 --  CONSTRUCTORS:
 --      UpdateObject(int clientID, int type)
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
 --  0-7     clientAction
 --  8-23    pos-X
 --  24-31   pos-Y
 --  32-39   rotation
 ----------------------------------------------------------------------------------------------------------*/

#include "updateobject.h"

using std::ostream;
using std::endl;

UpdateObject::UpdateObject(BYTE* buffer, size_t buffSize)
{
    memcpy(this, buffer, buffSize);
}

void UpdateObject::serialize(BYTE** buffer, size_t& buffSize)
{
    buffSize = sizeof(*this);
    (*buffer) = new BYTE[buffSize];
    memcpy((*buffer), this, buffSize);

    /*BYTE tmp;
     buffSize = 6;
     (*buffer) = new BYTE[6];
     memset((*buffer), 0, buffSize);

     BYTE* pActionBytes = 0;
     size_t numActionBytes = 1;
     actions_.serialize(&pActionBytes, numActionBytes);
     buffer[0] = pActionBytes;

     tmp = pos_.x() & 0xFFFF0000 >> 8;
     (*buffer)[1] = tmp;
     tmp = pos_.x() & 0x0000FFFF;
     (*buffer)[2] = tmp;

     tmp = pos_.y() & 0xFFFF0000 >> 8;
     (*buffer)[3] = tmp;
     tmp = pos_.y() & 0x0000FFFF;
     (*buffer)[4] = tmp;

     tmp = (BYTE)(rotation_ & 0x0000FFFF);
     (*buffer)[5] = tmp;*/
}
void UpdateObject::print(ostream& out)
{
    out << "Rotation: " << rotation_ << endl;
    out << "Position: " << pos_.rx() << ", " << pos_.ry() << endl;
    actions_.print(out);
}
