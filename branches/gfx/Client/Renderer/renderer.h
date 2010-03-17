#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <QGLWidget>
#include "../../Core/comm/data/updateobject.h"

//PI macros
#define PI              3.14159265358979323846
#define TWOPI           (2.0 * PI)
#define INVERSEPI       0.31830988618379067154

//Degree macros
#define DEGTORAD(a)     (a*PI/180.0)
#define RADTODEG(a)     (a*180.0/PI)

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
    char rotation;
    char objectWidthPx, objectHeightPx;
};

class Renderer : public QGLWidget
{
//vars
private:
    RenderObject renderList[MAXRENDERCOUNT];
    int renderCount;
    GLuint textures[3];

//funcs
public:
    Renderer(QWidget *parent);
    void Initialize();
    void Render();
    void buildRenderList(std::vector<UpdateObject> objectlist);

private:
    void resizeGL(int w, int h);
    void saveGLState();
    void restoreGLState();
};

#endif // RENDERER_H
