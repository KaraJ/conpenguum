#include "Physics.h"
#include <QPoint>
#include <math.h>
#include <QVector2D>

/*-----------------------------------------------------------------------------
--  FUNCTION:   rotVelToVec
--
--  DATE:       February 18, 2010
--
--  REVISIONS:  v0.1
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  rotVelToVec(int rot, int velocity)
--
--  NOTES:      Takes a rotation value and a velocity and returns the correct
--              vector. TASK: needs to be made more efficient.
--
--  RETURNS:    Qpoint style vector
--
------------------------------------------------------------------------------*/
QPoint rotVelToVec(int rot, int velocity)
{
    QPoint vector;
    //correcting the function here and removing the magic number
    double radians = DEGTORAD(rot);
    int x, y;
    y = sin(radians) * velocity/10;
    x = cos(radians) * velocity/10;
    vector.setX(x);
    vector.setY(y);
    return vector;
}

