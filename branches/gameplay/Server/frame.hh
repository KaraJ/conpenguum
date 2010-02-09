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
#ifndef FRAME_HH
#define FRAME_HH

#include <list>
#include "newtObjects.hh"
class frame{
public:
    std::list<ship> listShip;
    std::list<shot> listShot;
    // map
public:
    void tick();
    void addShip(ship newShip);
    void spawnShot(shot newShot);
    void fragShip(int shipID);
    void destroyShot(int shotID);
    void updateShips();
    void updateShots();
    // for testing
    void printShips();
};
#endif // FRAME_HH
