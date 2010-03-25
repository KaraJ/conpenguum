/*----------------------------------------------------------------------------
--
--  SOURCE FILE:    newObjects.h
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
#ifndef NEWTOBJECTS_H
#define NEWTOBJECTS_H

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
class NewtObject
{
public:
  QPoint position;
  QPoint vector;
  size_t id;
private:
    // next ID to be used
public:
    NewtObject(int pX, int pY, int vX, int vY, size_t ID): position(pX, pY),
        vector(vX ,vY), id(ID){}
    QPoint getPosition(){ return position; }
    QPoint getVector(){ return vector; }
    size_t getID(){ return id; }
private:
};
#endif // NEWTOBJCECTS_H
