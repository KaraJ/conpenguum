#ifndef GAMESOBJECT_H
#define GAMESOBJECT_H
#include <QPoint>
#include <vector>
#include <qstring.h>
#include <string>
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
        health = obj.getHealth();
        shield = obj.getShield();
    }

    inline void Update(UpdateObject &obj)
    {
        objectId = obj.getObjectId();
        angle = obj.getRotation();
        position = obj.getPos();
        health = obj.getHealth();
        shield = obj.getShield();
    }

	int objectId; //0 ~ 65535 Are real objects, 65537+ are transient objects
	int angle;  //Rotation angle 0-179
	int shield; //0-100
	int health; //0-100
	QPoint position; //XY position
	std::string textureName;  //Texture filename
	Animation currentAnime;
	Image *animeImage;
	size_t animeIndex; //Frame index (0 to 10 for ships)
	size_t objWidth;
	size_t objHeight;
	//int frameCounter; // For keeping track of how many frames have passed since last animation increment
	QString owner;
};

#endif
