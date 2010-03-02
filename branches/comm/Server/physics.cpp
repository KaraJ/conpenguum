#include <QPoint>
#include <math.h>


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
QPoint rotVelToVec(int rot, int velocity){
    QPoint vector;
    int x, y;
    double radians = (rot%90) / 57.29578;
    y = sin(radians)*velocity;
    x = cos(radians)*velocity;
    switch(rot / 90){
        case 0:
            break;
        case 1:
            y *= -1;
            break;
        case 2:
            y *= -1;
            x *= -1;
            break;
        case 3:
            x *= -1;
            break;
    }
    vector.setX(x);
    vector.setY(y);
    return vector;
}

