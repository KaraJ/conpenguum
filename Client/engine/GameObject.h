#ifndef GAMESOBJECT_H
#define GAMESOBJECT_H
#include <QPoint>
#include <vector>
#include <qstring.h>
#include "../Animation/Animation.h"
#include "../Animation/Image.h"
#include "../../Core/comm/data/updateobject.h"

//0 ~ 65536

class GameObject
{
public:
	int objectId;
	int angle; //Rotation angle 0-179
	QString text;  //Texture filename
	QPoint position; //XY position
	Animation currentAnime; //TODO: ?
	size_t animeIndex; //Frame index
    inline GameObject(){};
    inline GameObject(UpdateObject &obj)
    {
        objectID = obj.getObjectId();
        angle = obj.getRotation();
        position = obj.getPos();
    }
    inline Update(UpdateObject &obj)
    {
        objectID = obj.getObjectId();
        angle = obj.getRotation();
        position = obj.getPos();
    }

    int objectId;
    int angle;
    int animFrame;
    QString text;
    QPoint position;
    Image * animeImage;
    Animation currentAnime;
    size_t animeIndex;
};

#endif
