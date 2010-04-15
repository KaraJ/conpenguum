#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "resourceDefinitions.h"
#include "resourceEnums.h"
#include <map>
#include <QObject>
#include <QtXml>

class ResourceManager : public QObject
{
    Q_OBJECT
private:
    std::map<int, ResourceDefinition*> resourceMap;
    static ResourceManager* resourceManager;
    ResourceManager();
    QDomDocument *xmldoc;
public:
    static ResourceManager *GetInstance();
    ~ResourceManager();
    ResourceDefinition* GetResource(int ResourceType, int ResourceName);
};

#endif // RESOURCEMANAGER_H
