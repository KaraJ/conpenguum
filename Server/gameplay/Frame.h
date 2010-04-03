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
#include <vector>

#include "../../Core/comm/globals.h"
#include "Shot.h"
#include "Ship.h"
#include "NewtObjects.h"
#include "Map.h"
#include "Physics.h"
#include "../../Core/comm/data/clientaction.h"
#include "../../Core/comm/data/updateobject.h"

class Frame
{
private:
    int frameTimer;  // used to determine the lifetime of objects.
    //Map map;         // map used to determine ship/wall collisions as well as
                     // limit the number of comparisons needed for ship/shot
                     // collisions by keeping track of what objects occupy
                     // each tile.
public:
    Map map;
    Ship *listShip[MAX_CLIENTS]; // list of all ships(players) in the game.
    std::list<Shot> listShot; // list of all active shots in the game.
    std::list<NewtObject> listPwrup;

public:
    Frame(QString filename);
    void tick();
    void addShip(size_t clientID);
    void updateClientActions(std::vector <ClientAction>);
    void spawnShip(size_t shipID);
    void removeShip(size_t clientID);
    std::vector<UpdateObject> ListShip2listUpdateObject();
    void printShips(void);
    void printShots(void);
    void addPwrup(int x, int y) { listPwrup.push_back(NewtObject(x, y, 0, 0, 50)); }

private:
    int dist2Points(QVector2D point1, QVector2D point2);
    void fragShip(size_t shipID);
    void addShot(Shot newShot);
    Ship* getShip(size_t shipID);
    void updateShips();
    void updateShots();
    void destroyShot(size_t shotID);
};
#endif // FRAME_H
