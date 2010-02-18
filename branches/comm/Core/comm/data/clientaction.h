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

#include "bitmask.h"

//TODO: Make an enum for type

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
    ClientAction(int clientID, int type) : clientID_(clientID), type_(type) {}

    inline void clear() { ClientAction::mask_.Clear((ActionFlags)(AC_ACCELERATING | AC_FIREING | AC_TURNLEFT | AC_TURNRIGHT)); }
    inline void setFiring() { ClientAction::mask_.Set(AC_FIREING); }
    inline void setTurningLeft() { ClientAction::mask_.Set(AC_TURNLEFT); }
    inline void setTurningRight()  { ClientAction::mask_.Set(AC_TURNRIGHT); }
    inline void setAccelerating()  { ClientAction::mask_.Set(AC_ACCELERATING); }

    inline bool isFiring() { return ClientAction::mask_.Test(AC_FIREING); }
    inline bool isTurningRight() { return ClientAction::mask_.Test(AC_FIREING); }
    inline bool isTurningLeft() { return ClientAction::mask_.Test(AC_FIREING); }
    inline bool isAccelerating() { return ClientAction::mask_.Test(AC_FIREING); }
    inline int getClientID() { return clientID_; }
    inline int getType() { return type_; }
private:
    ActionBitmask mask_;
    int clientID_;
    int type_;
};

#endif
