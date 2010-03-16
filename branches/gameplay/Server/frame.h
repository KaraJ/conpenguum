/*----------------------------------------------------------------------------
--
--  SOURCE FILE:    frame.h
--
--  PROGRAM:        Compenguum
--
--  CLASSES:        frame
--
--  DATE:           January 27, 2010
--
--  REVISIONS:      v0.2 - Stubbed, sans ship/wall collision.
--                  v0.1 - basics, rest to be stubbed in.
--
--  DESIGNER:       Gameplay/Physics Team
--
--  PROGREMMER:     Gameplay/Physics Team
--
--  NOTES:          40% complete code. Testing functions intact and ship/wall
--                  collision omited.
--
----------------------------------------------------------------------------*/
#ifndef FRAME_H
#define FRAME_H

#include <QString>
#include <list>
#include "newtObjects.h"
#include "shot.h"
#include "ship.h"
#include "map.h"
class Frame{
private:
    int frameTimer;  // used to determine the lifetime of objects.
    Map map;         // map used to determine ship/wall collisions as well as
                     // limit the number of comparisons needed for ship/shot
                     // collisions by keeping track of what objects occupy
                     // each tile.
public:
    std::list<Ship> listShip; // list of all ships(players) in the game.
    std::list<Shot> listShot; // list of all active shots in the game.
public:
    Frame(QString filename): frameTimer(0), map(filename){};
    void tick();
    void addShip(Ship newShip);
    void addShot(Shot newShot);
    std::list<Ship>::iterator getShip(int shipID);
    void fragShip(int shipID);
    void spawnShip(int shotID);
    void destroyShot(int shotID);
    void updateShips();
    void updateShots();
    // for testing
    void printShips();
    int dist2Points(QPoint point1, QPoint point2);
    void updateShips(bool thrustF,bool thrustR, bool rotL, bool rotR, bool fire);
    void drawMap(){map.drawMap();}
    int testCanMove(QPoint p, bool v, int s, int d){return map.canMove(p,v,s,d);}
};
#endif // FRAME_H
