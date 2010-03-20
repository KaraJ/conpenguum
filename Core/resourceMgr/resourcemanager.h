#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "md5.hh"
#include "resourceDefinitions.h"
#include <map>

class ResourceManager
{
private:
    MD5 md5;
    std::map<int, ResourceDefinition*> resourceMap;
public:
    ResourceManager();
    ~ResourceManager();
    ResourceDefinition* GetResource(int ResourceType, int ResourceName);
};

#endif // RESOURCEMANAGER_H
