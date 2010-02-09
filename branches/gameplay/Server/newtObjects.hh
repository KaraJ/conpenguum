/*----------------------------------------------------------------------------
--
--  SOURCE FILE:    newObjects.hh
--
--  PROGRAM:        Compenguum
--
--  CLASSES:        newtObject
--                  ship : newtObject
--                  shot : newtObject
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
--  CLASSE:         newtObject
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
class newtObject{
public:
    QPoint position;
    QPoint vector;
    int id;
private:
    // frame counter
    // next ID to be used
public:
    newtObject(): position(0,0), vector(0,0), id(0){}
    newtObject(int pX, int pY, int vX, int vY, int ID): position(pX, pY),
        vector(vX ,vY), id(ID){}
    QPoint getPosition(){ return position; }
    QPoint getVector(){ return vector; }
    int getID(){ return id; }
private:
};

/*----------------------------------------------------------------------------
--
--  CLASSE:         ship
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
class ship : public newtObject {
private:
    int rotation;
public:
    ship(): rotation(0) {}
    ship(int pX, int pY, int vX, int vY, int ID):
        newtObject(pX, pY, vX, vY, ID){}
    int getRot(){ return rotation; }
};

/*----------------------------------------------------------------------------
--
--  CLASSE:         shot
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
class shot: public newtObject {
    //
};


#endif // NEWTOBJCECTS_HH
