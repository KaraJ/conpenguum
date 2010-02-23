#ifndef RENDERER_H
#define RENDERER_H

#include <QGLWidget>

struct RenderObject
{
    GLuint texture, xLocation, yLocation;
    GLfloat textureXOffset, textureYOffset;
    GLshort width, height;
};

class Renderer : public QGLWidget
{
private:
    RenderObject RenderList[4096];
    QPoint anchor;
    float scale;
    float rot_x, rot_y, rot_z;
    GLuint tile_list;
    GLfloat *wave;

public:
    Renderer(QWidget *parent);
    void Initialize();
    void Render();
    int x,y;
//    void paintEvent(QPaintEvent *);

private:
    void resizeGL(int w, int h);
    void saveGLState();
    void restoreGLState();
    void BuildRenderList();
};

#endif // RENDERER_H
