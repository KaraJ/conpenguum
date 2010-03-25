#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <QGLWidget>
#include "../../Core/comm/data/updateobject.h"
#include <map>
#include "../../Core/resourceMgr/resourcemanager.h"


//PI macros
#define PI              3.14159265358979323846
#define TWOPI           (2.0 * PI)
#define INVERSEPI       0.31830988618379067154

//Degree macros
#define RADIANSINDEG    0.017453293 //PI/180
#define DEGREESINRAD    57.295779513 //180/PI
#define DEGTORAD(a)     ((a)*RADIANSINDEG)
#define RADTODEG(a)     ((a)*DEGREESINRAD)

#define SCREENWIDTH     1024
#define SCREENHEIGHT    768
#define SCRCENTREW      512
#define SCRCENTREH      384
#define MAXRENDERCOUNT  40000

struct RenderObject
{
    short x, y;
    GLuint texture;
    float texOffsetX, texOffsetY;
    float objectWidth, objectHeight;
    int rotation;
    int objectWidthPx, objectHeightPx;
};

class Renderer : public QGLWidget
{
//vars
private:
    ResourceManager* resourceManager;
    RenderObject renderList[MAXRENDERCOUNT];
    int renderCount;
    //GLuint textures[3];
    std::map<std::string, GLuint> textures;
    std::vector<UpdateObject> &objectlist;
//funcs
public:
    Renderer(QWidget *parent, std::vector<UpdateObject> &gameSt);
    void Initialize();
    void Render();
    void buildRenderList();

private:
    void resizeGL(int w, int h);
    void saveGLState();
    void restoreGLState();
};

#endif // RENDERER_H

