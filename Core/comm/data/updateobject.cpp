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
 ----------------------------------------------------------------------------------------------------------*/

#include "updateobject.h"

using std::ostream;
using std::endl;

/*----------------------------------------------------------------------------------------------------------
--  FUNCTION: UpdateObject(ClientAction& a)
--
--  INTERFACE:
--      UpdateObject(ClientAction& a)
--          a:  The client action
--
--  RETURNS: new UpdateObject
----------------------------------------------------------------------------------------------------------*/
UpdateObject::UpdateObject(ClientAction& a) : rotation_(0), pos_(), actions_(a)
{

}

/*----------------------------------------------------------------------------------------------------------
--  FUNCTION: UpdateObject(int objID)
--
--  INTERFACE:
--      UpdateObject(int objID)
--          objectID:   objIDs 0-31 are reserved for players. objIDs 32-155 can be used for bullets,
--                      explosions, robot unicorns, etc.
--
--  RETURNS: new UpdateObject
----------------------------------------------------------------------------------------------------------*/
UpdateObject::UpdateObject(int objID) : rotation_(0), pos_(), actions_(ClientAction(objID))
{

}

/*----------------------------------------------------------------------------------------------------------
--  FUNCTION: UpdateObject(BYTE* buffer)
--
--  INTERFACE:
--      UpdateObject(BYTE* buffer)
--          buffer: byte array, should be the same one returned from a UpdateObject::serialise() call or
--                  strangeness will occur.
--
--  RETURNS: new UpdateObject
----------------------------------------------------------------------------------------------------------*/
UpdateObject::UpdateObject(BYTE* buffer) : actions_(0)
{
    int x = 0, y = 0;

    actions_ = ClientAction(buffer);
    x = buffer[2] << 8;
    x |= buffer[3];
    y = buffer[4] << 8;
    y |= buffer[5];
    pos_.setX(x);
    pos_.setY(y);
    rotation_ = (size_t)buffer[6];
}

/*----------------------------------------------------------------------------------------------------------
--  FUNCTION: serialise(BYTE** buffer)
--
--  INTERFACE:
--      UpdateObject(BYTE** buffer)
--          buffer: pointer to a byte array, will be filled with bytes that can be passed to the
--                  second constructor
-- NOTES:
--     Packet Structure
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- Byte    Bits
--         0   1   2   3   4   5   6   7
--  0      CA  CA  CA  CA  CA  CA  CA  CA
--         8   9   10  11  12  13  14  15
--  1      CA  CA  CA  CA  CA  CA  CA  CA
--         16  17  18  19  20  21  22  23
--  2      PX1 PX1 PX1 PX1 PX1 PX1 PX1 PX1
--         24  25  26  27  28  29  30  31
--  3      PX2 PX2 PX2 PX2 PX2 PX2 PX2 PX2
--         32  33  34  35  36  37  38  39
--  4      PY1 PY1 PY1 PY1 PY1 PY1 PY1 PY1
--         40  41  42  43  44  45  46  47
--  5      PY2 PY2 PY2 PY2 PY2 PY2 PY2 PY2
--         48  49  50  51  52  53  54  55
--  6      R   R   R   R   R   R   R   R
----------------------------------------------------------------------------------------------------------*/
void UpdateObject::serialise(BYTE** buffer) const
{
     (*buffer) = new BYTE[serializeSize];
     memset((*buffer), 0, serializeSize);

     BYTE* pActionBytes = 0;
     actions_.serialise(&pActionBytes);
     memcpy((*buffer), pActionBytes, ClientAction::serialiseSize);

     size_t x = (size_t)pos_.x();
     size_t y = (size_t)pos_.y();
     (*buffer)[2] = (BYTE)((x & 0x0000FF00) >> 8);
     (*buffer)[3] = (BYTE)(x & 0x000000FF);
     (*buffer)[4] = (BYTE)((y & 0x0000FF00) >> 8);
     (*buffer)[5] = (BYTE)(y & 0x000000FF);
     (*buffer)[6] = (BYTE)(rotation_ & 0x0000FFFF);
}

void UpdateObject::print(ostream& out)
{
    out << "Rotation: " << rotation_ << endl;
    out << "Position: " << pos_.rx() << ", " << pos_.ry() << endl;
    actions_.print(out);
}
