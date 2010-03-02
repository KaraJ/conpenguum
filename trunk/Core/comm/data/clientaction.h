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

//TODO: Make an enum for type
//TODO: add decelerating? (ask game-play team)

enum ActionFlags
{
    AC_FIREING  = 0x01,
    AC_TURNLEFT = 0x02,
    AC_TURNRIGHT  = 0x04,
    AC_ACCELERATING = 0x08
};

typedef Bitmask<unsigned, ActionFlags> ActionBitmask;

class ClientAction
{
public:
    static const int serializeSize = 2;

    ClientAction(int clientID) : clientID_(clientID)
    {
        if (clientID > 31)
            throw "ClientID must be between 0 and 31 (inclusive)";
    }
    ClientAction(BYTE* buffer);

    inline void clear() { mask_.Clear((ActionFlags)(AC_ACCELERATING | AC_FIREING | AC_TURNLEFT | AC_TURNRIGHT)); }
    inline void setFiring() { mask_.Set(AC_FIREING); }
    inline void setTurningLeft() { mask_.Set(AC_TURNLEFT); }
    inline void setTurningRight()  { mask_.Set(AC_TURNRIGHT); }
    inline void setAccelerating()  { mask_.Set(AC_ACCELERATING); }

    inline bool isFiring() const { return mask_.Test(AC_FIREING); }
    inline bool isTurningLeft() const { return mask_.Test(AC_TURNLEFT); }
    inline bool isTurningRight() const { return mask_.Test(AC_TURNRIGHT); }
    inline bool isAccelerating() const { return mask_.Test(AC_ACCELERATING); }
    inline int getClientID() const { return clientID_; }
    void serialize(BYTE** buffer) const;
    void print(std::ostream& out = std::cout);
private:
    ActionBitmask mask_;
    int clientID_;
};

#endif
