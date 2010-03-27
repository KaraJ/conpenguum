#ifndef SHOT_H
#define SHOT_H

#include "NewtObjects.h"

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
class Shot: public NewtObject
{
private:
    // int shotType;  // the type of shot
public:
    int deathTime; // the frame time in which the shot dies
private:
public:
    Shot(int pX, int pY, int vX, int vY, int ID, int death): 
    	NewtObject(pX, pY, vX, vY, ID), deathTime(death){}
    void updateShotPos();
};

#endif // SHOT_H
