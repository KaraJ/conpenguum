#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "resourceDefinitions.h"
#include <map>
#include <QObject>

class ResourceManager : public QObject
{
    Q_OBJECT
private:
    std::map<int, ResourceDefinition*> resourceMap;
    static ResourceManager* resourceManager;
    ResourceManager();
public:
    static ResourceManager *GetInstance();
    ~ResourceManager();
    ResourceDefinition* GetResource(int ResourceType, int ResourceName);
};

#endif // RESOURCEMANAGER_H
