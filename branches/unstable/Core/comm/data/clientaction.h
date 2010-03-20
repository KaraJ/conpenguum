/*----------------------------------------------------------------------------------------------------------
--  SOURCE FILE: clientAction.h
--
--  PROGRAM: TuxSpace
--
--  CONSTRUCTORS:
--      ClientAction(int clientID, int type)
--  METHODS:
--      void clear()
--      void setFiring()
--      void setTurningLeft()
--      void setTurningRight()
--      void setAccelerating()
--      bool isFiring()
--      bool isTurningRight()
--      bool isTurningLeft()
--      bool isAccelerating()
--      int getClientID()
--      int getType()
--
--  PROGRAMMER: Ben Barbour
--
--  REVISIONS (date and description):
--
--  DATE: 2010-01-23
--
--  NOTES: Wraps the state of all player actions during any given frame
----------------------------------------------------------------------------------------------------------*/

#ifndef CLIENTACTION_H
#define CLIENTACTION_H

#define BYTE unsigned char

#include "../globals.h"
#include "bitmask.h"
#include <cstring>
#include <iostream>

enum ActionFlags
{
    AC_FIREING  = 0x01,
    AC_TURNLEFT = 0x02,
    AC_TURNRIGHT  = 0x04,
    AC_ACCELERATING = 0x08,
    AC_DECCELERATING = 0x10
};

typedef Bitmask<unsigned int, ActionFlags> ActionBitmask;

class ClientAction
{
public:
    static const int serialiseSize = 2;

    ClientAction(int objID);
    ClientAction(BYTE* buffer);

    inline void clear() { mask_.Clear((ActionFlags)(AC_FIREING | AC_TURNLEFT | AC_TURNRIGHT | AC_ACCELERATING | AC_DECCELERATING)); }
    inline void setFiring() { mask_.Set(AC_FIREING); }
    inline void unsetFiring() { mask_.Clear(AC_FIREING); }
    inline void setTurningLeft() { mask_.Set(AC_TURNLEFT); }
    inline void unsetTurningLeft() { mask_.Clear(AC_TURNLEFT); }
    inline void setTurningRight()  { mask_.Set(AC_TURNRIGHT); }
    inline void unsetTurningRight()  { mask_.Clear(AC_TURNRIGHT); }
    inline void setAccelerating()  { mask_.Set(AC_ACCELERATING); }
    inline void unsetAccelerating()  { mask_.Clear(AC_ACCELERATING); }
    inline void setDecelerating() { mask_.Set(AC_DECCELERATING); }
    inline void unsetDecelerating() { mask_.Clear(AC_DECCELERATING); }

    inline bool isFiring() const { return mask_.Test(AC_FIREING); }
    inline bool isTurningLeft() const { return mask_.Test(AC_TURNLEFT); }
    inline bool isTurningRight() const { return mask_.Test(AC_TURNRIGHT); }
    inline bool isAccelerating() const { return mask_.Test(AC_ACCELERATING); }
    inline bool isDecelerating() const { return mask_.Test(AC_DECCELERATING); }
    inline int getObjectID() const { return objID_; }
    void serialise(BYTE** buffer) const;
    void print(std::ostream& out = std::cout);
private:
    ActionBitmask mask_;
    unsigned short objID_;
};

#endif
