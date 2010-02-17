/*----------------------------------------------------------------------------
--
--  SOURCE FILE:    frame.hh
--
--  PROGRAM:        Compenguum
--
--  CLASSES:        frame
--
--  DATE:           January 27, 2010
--
--  REVISIONS:      v0.1 - basics, rest to be stubbed in
--
--  DESIGNER:       Gameplay/Physics Team
--
--  PROGREMMER:     Gameplay/Physics Team
--
--  NOTES:          basics, rest to be stubbed in
--
----------------------------------------------------------------------------*/
#ifndef FRAME_H
#define FRAME_H

#include <list>
#include "newtObjects.h"
class frame{
public:
    std::list<Ship> listShip;
    std::list<Shot> listShot;
    // map
public:
    void tick();
    void addShip(Ship newShip);
    void spawnShot(Shot newShot);
    void fragShip(int shipID);
    void destroyShot(int shotID);
    void updateShips();
    void updateShots();
    // for testing
    void printShips();
};
#endif // FRAME_H
