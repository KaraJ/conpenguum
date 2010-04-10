#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <deque>
#include <QGLWidget>
#include "../../Core/comm/data/updateobject.h"
#include "../engine/GameObject.h"
#include <map>
#include "../../Core/resourceMgr/resourcemanager.h"
#include "../engine/Map.h"
#include "../../Core/Player.h"

//PI macros
#define PI              3.14159265358979323846
#define TWOPI           (2.0 * PI)
#define INVERSEPI       0.31830988618379067154

#define SCREENWIDTH     1024
#define SCREENHEIGHT    768
#define SCRCENTREW      512
#define SCRCENTREH      384
#define MAXRENDERCOUNT  40000

struct RenderObject
{
    short x, y, textX, textY;
    GLuint texture;
    float texOffsetX, texOffsetY;
    float objectWidth, objectHeight;
    int rotation;
    int objectWidthPx, objectHeightPx;
    int health, shield;
    int objectId;
    QString name;
};

class Renderer : public QGLWidget
{
//vars
private:
    ResourceManager* resourceManager;
    RenderObject renderList[MAXRENDERCOUNT];
    int renderCount;
    std::map<std::string, GLuint> textures;
    std::map<int, GameObject> &objectlist;
    std::deque<QString> *chatText_;
    QString *localText_;
    int mapTileCount;
    int deathTime_;
    Map *map;
//funcs
public:
    //Renderer(QWidget *parent, std::vector<UpdateObject> &gameSt);
    Renderer(QWidget *parent, std::map<int, GameObject> &gameSt, std::deque<QString> *chatText, QString *localText);
    void Initialize();
    void Render(int clientId, const std::vector<Player> &playerList);
    void buildRenderList(QPoint center);
    void loadMap(Map *map);
    void setDeathTime(int time) { deathTime_ = time; }

private:
    void resizeGL(int w, int h);
    void saveGLState();
    void restoreGLState();
};

#endif // RENDERER_H

