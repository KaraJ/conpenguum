#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "md5.hh"

class ResourceManager
{
private:
    MD5 md5;
public:
    ResourceManager();
    int GetResource(int ResourceType, int ResourceName);
};

#endif // RESOURCEMANAGER_H
