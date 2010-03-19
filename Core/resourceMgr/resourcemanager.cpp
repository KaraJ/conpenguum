#include "resourcemanager.h"
#include "resourceEnums.h"
#include <QtXml>

ResourceManager::ResourceManager()
{
}

int ResourceManager::GetResource(int ResourceType, int ResourceName)
{
    switch(ResourceType)
    {
    case SHIP:
        //return hash value for this object from the map...or possibly a basic object that
        //contains values for textures/animations/others....for now, it's value 1
        return 1;
    case SHOT:
        return 2;
    default:
        return -1;
    }
}
