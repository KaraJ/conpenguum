#ifndef GAMESOBJECT_H
#define GAMESOBJECT_H
#include <QPoint>
#include <vector>
#include <qstring.h>
#include "../Animation/Animation.h"
#include "../Animation/Image.h"
#include "../../Core/comm/data/updateobject.h"

struct GameObject
{
public:
    inline GameObject(){};
    inline GameObject(UpdateObject &obj)
    {
        objectId = obj.getObjectId();
        angle = obj.getRotation();
        position = obj.getPos();
    }

    inline void Update(UpdateObject &obj)
    {
        objectId = obj.getObjectId();
        angle = obj.getRotation();
        position = obj.getPos();
    }

	int objectId; //0 ~ 65535 Are real objects, 65537+ are transient objects
	int angle; //Rotation angle 0-179
	QPoint position; //XY position
	QString text;  //Texture filename
	Animation currentAnime; //TODO: ?
	size_t animeIndex; //Frame index
};

#endif
