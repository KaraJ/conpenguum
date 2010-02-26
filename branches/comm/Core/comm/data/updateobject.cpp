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
 --     Packet Structure
 -- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 -- Byte    Bits
 --         0   1   2   3   4   5   6   7
 --  0      CA  CA  CA  CA  CA  CA  CA  CA
 --         8   9   10  11  12  13  14  15
 --  1      CA  R   R   R   R   R   R   R
 --         16  17  18  19  20  21  22  23
 --  2      PX1 PX1 PX1 PX1 PX1 PX1 PX1 PX1
 --         24  25  26  27  28  29  30  31
 --  3      PX2 PX2 PX2 PX2 PX2 PX2 PX2 PX2
 --         32  33  34  35  36  37  38  39
 --  4      PY1 PY1 PY1 PY1 PY1 PY1 PY1 PY1
 --         40  41  42  43  44  45  46  47
 --  5      PY2 PY2 PY2 PY2 PY2 PY2 PY2 PY2
 ----------------------------------------------------------------------------------------------------------*/

#include "updateobject.h"

using std::ostream;
using std::endl;

UpdateObject::UpdateObject(BYTE* buffer) : actions_(0)
{
    int x = 0, y = 0;

    actions_ = ClientAction(buffer);
    rotation_ = (size_t)(buffer[1] & 0x7F);
    x = buffer[2] << 8;
    x |= buffer[3];
    y = buffer[4] << 8;
    y |= buffer[5];
    pos_.setX(x);
    pos_.setY(y);
}

void UpdateObject::serialize(BYTE** buffer)
{
     BYTE tmp;
     (*buffer) = new BYTE[serializeSize];
     memset((*buffer), 0, serializeSize);

     BYTE* pActionBytes = 0;
     actions_.serialize(&pActionBytes);
     memcpy((*buffer), pActionBytes, ClientAction::serializeSize);

     tmp = (BYTE)(rotation_ & 0x00007FFF);
     (*buffer)[1] |= tmp;
     size_t x = (size_t)pos_.x();
     size_t y = (size_t)pos_.y();
     (*buffer)[2] = (BYTE)((x & 0x0000FF00) >> 8);
     (*buffer)[3] = (BYTE)(x & 0x000000FF);
     (*buffer)[4] = (BYTE)((y & 0x0000FF00) >> 8);
     (*buffer)[5] = (BYTE)(y & 0x000000FF);
}

void UpdateObject::print(ostream& out)
{
    out << "Rotation: " << rotation_ << endl;
    out << "Position: " << pos_.rx() << ", " << pos_.ry() << endl;
    actions_.print(out);
}
