#ifndef SHOT_H
#define SHOT_H

#include "newtObjects.h"

/*----------------------------------------------------------------------------
--
--  CLASS:         shot
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
class Shot: public NewtObject
{
private:
    // int shotType;  // the type of shot
    // int deathTime; // the frame time in which the shot dies
public:
private:
public:
    Shot(int pX, int pY, int vX, int vY, int ID): NewtObject(pX, pY, vX, vY, ID){}
    void updateShotPos();
};

#endif // SHOT_H
