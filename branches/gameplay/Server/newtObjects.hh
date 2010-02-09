/*----------------------------------------------------------------------------
--
--  SOURCE FILE:    newObjects.hh
--
--  PROGRAM:        Compenguum
--
--  CLASSES:        NewtObject
--                  Ship : NewtObject
--                  Shot : NewtObject
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
#ifndef NEWTOBJECTS_HH
#define NEWTOBJECTS_HH

#include <QPoint>

/*----------------------------------------------------------------------------
--
--  CLASSE:         NewtObject
--
--  DATE:           January 27, 2010
--
--  REVISIONS:      v0.1 - basics, rest to be stubbed in
--
--  DESIGNER:       Gameplay/Physics Team
--
--  PROGREMMER:     Gameplay/Physics Team
--
--  NOTES:          Newtonian objects. The basic moving object class.
--
----------------------------------------------------------------------------*/
class NewtObject{
public:
    QPoint position;
    QPoint vector;
    int id;
private:
    // frame counter
    // next ID to be used
public:
    NewtObject(): position(0,0), vector(0,0), id(0){}
    NewtObject(int pX, int pY, int vX, int vY, int ID): position(pX, pY),
        vector(vX ,vY), id(ID){}
    QPoint getPosition(){ return position; }
    QPoint getVector(){ return vector; }
    int getID(){ return id; }
private:
};

/*----------------------------------------------------------------------------
--
--  CLASSE:         Ship
--
--  DATE:           January 27, 2010
--
--  REVISIONS:      v0.1 - basics, rest to be stubbed in
--
--  DESIGNER:       Gameplay/Physics Team
--
--  PROGREMMER:     Gameplay/Physics Team
--
--  NOTES:          A newtObject with rotation. The basis of a player
--                  controlled ship.
--
----------------------------------------------------------------------------*/
class Ship : public NewtObject {
private:
    int rotation;
public:
    Ship(): rotation(0) {}
    Ship(int pX, int pY, int vX, int vY, int ID):
        NewtObject(pX, pY, vX, vY, ID){}
    int getRot(){ return rotation; }
};

/*----------------------------------------------------------------------------
--
--  CLASSE:         Shot
--
--  DATE:           January 27, 2010
--
--  REVISIONS:      v0.1 - basics, rest to be stubbed in
--
--  DESIGNER:       Gameplay/Physics Team
--
--  PROGREMMER:     Gameplay/Physics Team
--
--  NOTES:          The basis of the shots that players shoot.
--
----------------------------------------------------------------------------*/
class Shot: public NewtObject {
    //
};


#endif // NEWTOBJCECTS_HH
