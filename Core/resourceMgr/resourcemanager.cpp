#include "resourcemanager.h"
#include "resourceEnums.h"
#include <QtXml>

//initialize singleton pointer
ResourceManager::resourceManager = NULL;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
    for(std::map<int, ResourceDefinition*>::iterator it = resourceMap.begin(); it!=resourceMap.end(); it++)
    {
        delete it->second;
    }
}

ResourceManager::GetInstance()
{
    if(!resourceManager)
        resourceManager = new ResourceManager();
    return resourceManager;
}

ResourceDefinition* ResourceManager::GetResource(int ResourceType, int ResourceName)
{
    int key = (ResourceType<<16) + ResourceName;

    //check if we've already loaded this resource
    if(resourceMap.find(key))
        return resourceMap[key];

    switch(ResourceType)
    {
    case SHIP:
        {
            QDomDocument doc("ships");
            QFile file(":/resources/ships.xml");
            if (!file.open(QIODevice::ReadOnly))
                return;
            if (!doc.setContent(&file)) {
                file.close();
                return;
            }
            file.close();
            ShipDefinition *rd = new ShipDefinition();
            //grab the first child of the root element
            QDomNode n = doc.documentElement().firstChild();
            while(!n.isNull())
            {
                QDomElement ship = n.toElement();
                //skip if not an element node
                if(ship.isNull())
                {
                    n=n.nextSibling();
                    continue;
                }
                //skip if not the node we're looking for
                if(ship.attribute("type").toInt() != ResourceName)
                {
                    n=n.nextSibling();
                    continue;
                }
                QDomElement data = ship.firstChildElement();
                rd->velocity_thrust = data.text().toInt();
                data = data.nextSibling();
                rd->velocity_shot = data.text().toInt();
                data = data.nextSibling();
                rd->velocity_max = data.text().toInt();
                data = data.nextSibling();
                rd->rotation_rate = data.text().toInt();
                data = data.nextSibling();
                rd->ship_hit_dist = data.text().toInt();
                data = data.nextSibling();
                rd->texture = data.text().toStdString();
                data = data.nextSibling();
                rd->texture_xoffset = data.text().toFloat();
                data = data.nextSibling();
                rd->texture_yoffset = data.text().toFloat();
                data = data.nextSibling();
                rd->texture_width = data.text().toFloat();
                data = data.nextSibling();
                rd->texture_height = data.text().toFloat();
                data = data.nextSibling();
                rd->object_width = data.text().toInt();
                data = data.nextSibling();
                rd->object_height = data.text().toInt();

                break;
            }
            resourceMap.insert(std::pair<int,ResourceDefinition*>(key,rd));
            return rd;
        }
    case SHOT:
        QDomDocument doc("shots");
        QFile file(":/resources/shots.xml");
        if (!file.open(QIODevice::ReadOnly))
            return;
        if (!doc.setContent(&file)) {
            file.close();
            return;
        }
        file.close();
        ShotDefinition *rd = new ShotDefinition();
        //grab the first child of the root element
        QDomNode n = doc.documentElement().firstChild();
        while(!n.isNull())
        {
            QDomElement shot = n.toElement();
            //skip if not an element node
            if(shot.isNull())
            {
                n=n.nextSibling();
                continue;
            }
            //skip if not the node we're looking for
            if(shot.attribute("type").toInt() != ResourceName)
            {
                n=n.nextSibling();
                continue;
            }
            QDomElement data = shot.firstChildElement();
            rd->texture = data.text().toStdString();
            data = data.nextSibling();
            rd->texture_xoffset = data.text().toFloat();
            data = data.nextSibling();
            rd->texture_yoffset = data.text().toFloat();
            data = data.nextSibling();
            rd->texture_width = data.text().toFloat();
            data = data.nextSibling();
            rd->texture_height = data.text().toFloat();
            data = data.nextSibling();
            rd->object_width = data.text().toInt();
            data = data.nextSibling();
            rd->object_height = data.text().toInt();

            break;
        }
        resourceMap.insert(std::pair<int,ResourceDefinition*>(key,rd));
        return rd;
    }
    default:
        return NULL;
    }
}
