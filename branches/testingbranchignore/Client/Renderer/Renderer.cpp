#include "Renderer.h"
//#include "rendererDefines.h"
#include <QtGlobal>
#include <QPainter>

Renderer::Renderer(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers|QGL::AlphaChannel), parent)
{
}

/*void Renderer::paintEvent(QPaintEvent *)
{
    Render();
}*/


void Renderer::Initialize()
{
    //set GL flags
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_SMOOTH);
    qglClearColor(Qt::black);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //Set the clear color
}

void Renderer::resizeGL(int w, int h)
{
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);
}

void Renderer::Render()
{
    QImage tex("../textures/bg01.bmp");
    glBindTexture(GL_TEXTURE_2D, bindTexture(tex,GL_TEXTURE_2D));

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glOrtho(0,1,0,1,-1,1);
    glBegin(GL_POLYGON);
        glVertex3f(0.25,0.25,0.0);
        glVertex3f(0.75,0.25,0.0);
        glVertex3f(0.75,0.75,0.0);
        glVertex3f(0.25,0.75,0.0);
    glEnd();
    glFlush();
    //TODO: This is the text rendering part, this should be moved out to it's own function
    /*QPainter p(this); // used for text overlay
    saveGLState();
    // draw the overlayed text using QPainter
    p.setPen(QColor(197, 197, 197, 157));
    p.setBrush(QColor(197, 197, 197, 127));
    p.drawRect(QRect(0, 0, width(), 50));
    p.setPen(Qt::black);
    p.setBrush(Qt::NoBrush);
    const QString str1(tr("A simple OpenGL framebuffer object example."));
    const QString str2(tr("Use the mouse wheel to zoom, press buttons and move mouse to rotate, double-click to flip."));
    QFontMetrics fm(p.font());
    p.drawText(width()/2 - fm.width(str1)/2, 20, str1);
    p.drawText(width()/2 - fm.width(str2)/2, 20 + fm.lineSpacing(), str2);*/
}


void Renderer::saveGLState()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
}

void Renderer::restoreGLState()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}
