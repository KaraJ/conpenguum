#ifndef RENDERER_H
#define RENDERER_H

#include <QGLWidget>
#include <QGLFramebufferObject>
//#include <QGLFramebufferObjectFormat>

class Renderer : public QGLWidget
{
private:
    QPoint anchor;
    float scale;
    float rot_x, rot_y, rot_z;
    GLuint tile_list;
    GLfloat *wave;

    QGLFramebufferObject *render_fbo;
    QGLFramebufferObject *texture_fbo;

public:
    Renderer(QWidget *parent);
    void Initialize();
    void Render();
//    void paintEvent(QPaintEvent *);

private:
    void resizeGL(int w, int h);
    void saveGLState();
    void restoreGLState();
};

#endif // RENDERER_H
