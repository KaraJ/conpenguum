#include "MapTile.h"
#include "../../Core/resourceMgr/resourcemanager.h"

MapTile::MapTile(int texTileNum, int mapRow, int mapCol)
{
    tileID = texTileNum;
    TexturedResourceDefinition *rd = (TexturedResourceDefinition*)ResourceManager::GetInstance()->GetResource(TILE, texTileNum);
    pos_.setX(mapCol * rd->object_height);
    pos_.setY(mapRow * rd->object_width);
}

MapTile::~MapTile()
{

}
