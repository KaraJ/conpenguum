#include "renderer.h"
#include "rendererDefines.h"
#include <QtGlobal>
#include <QPainter>
#include <QtGui>
#include <QGLWidget>
#include <QtOpenGL>

#define checkImageWidth 64
#define checkImageHeight 64
static GLuint texName;

Renderer::Renderer(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers|QGL::AlphaChannel), parent)
{
}

/*void Renderer::paintEvent(QPaintEvent *)
{
    Render();
}*/


void Renderer::Initialize()
{
    makeCurrent();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    texName = bindTexture(QPixmap(QString(":/textures/bg07.bmp"),"BMP"), GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}

void Renderer::BuildRenderList()
{
    //iterate over the map
    //I imagine, if we use an array for the map (fast) we would have something like
    //for(int i = 0; i < GameMap::GetInstance()->tileCount; i++);
    //in fact, we should probably narrow that loop down based on our viewport...
    //int x,y,k=0;
    //GetViewPortTopLeft(x,y);
    //for(int i = x/tileWidth; i<viewPortWidth/tileWidth; i++)
    //  for(int j = y/tileheight; j .......etc)
    //  {    renderList[k] = gameMap[i][j]; k++; }

    //iterate over the gamestate object for items within our viewport.
    //for(iterator::begin .....)
    // if(item is in viewport)
    //   renderlist[k] = .....
}

void Renderer::resizeGL(int w, int h)
{
    glViewport(0,0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-3.6);
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble) h );
}

void Renderer::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texName);
    glBegin(GL_QUADS);
    //for(int i = 0; i < renderListSize; i++)
    //{
    //  RenderObject rob = renderList[i];
    //  glTexCoord2f = (rob.xOffset, rob.yOffset); glVertex3f(rob.x-rob.width/2, rob.y-rob.height/2);
    //  glTexCoord2f = (rob.xOffset, rob.yOffset); glVertex3f(rob.x-rob.width/2, rob.y+rob.height/2);
    //  glTexCoord2f = (rob.xOffset, rob.yOffset); glVertex3f(rob.x+rob.width/2, rob.y+rob.height/2);
    //  glTexCoord2f = (rob.xOffset, rob.yOffset); glVertex3f(rob.x+rob.width/2, rob.y-rob.height/2);
    //}
    glTexCoord2f(0.0,0.0); glVertex3f(x, x, 0.0);
    glTexCoord2f(0.0,1.0); glVertex3f(x, y, 0.0);
    glTexCoord2f(1.0,1.0); glVertex3f(y, y, 0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(y, x, 0.0);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);

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
    updateGL();
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
