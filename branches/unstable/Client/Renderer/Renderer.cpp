#include "Renderer.h"
#include <QtGlobal>
#include <QPainter>
#include <QtGui>
#include <QGLWidget>
#include <QtOpenGL>
#include <cmath>
#include <vector>
#include <cassert>
#include <sstream>
#include "../../Core/resourceMgr/resourceEnums.h"

using namespace std;

Renderer::Renderer(QWidget *parent,std::map<int, GameObject> &gameSt, QString *chatText) :
		QGLWidget(QGLFormat(QGL::SampleBuffers|QGL::AlphaChannel), parent), objectlist(gameSt), chatText_(chatText)
//Renderer::Renderer(QWidget *parent,std::vector<UpdateObject> &gameSt) : QGLWidget(QGLFormat(QGL::SampleBuffers|QGL::AlphaChannel), parent), objectlist(gameSt)
{
    const char *glVersion = (const char*)glGetString(GL_VERSION);
    double glVer = atof(glVersion);
    assert(glVer > 1.1);
    //resourceManager = ResourceManager::GetInstance();
    Initialize();
    this->resize(SCREENWIDTH,SCREENHEIGHT);
}

void Renderer::buildRenderList(QPoint center)
{
    //if we have more than 40k render objects, we're fucked.
    assert(MAXRENDERCOUNT > objectlist.size()/*+map objects*/);

    size_t i, xOffset, yOffset;

    //grab the first render object, this should be the client's ship, and thus our center
    xOffset = center.x();
    yOffset = center.y();

    //sample code for getting a texture from resource manager
    //you need to know the type of the resource you are getting, so you can
    //properly cast to the correct struct type
    //textures[(ShipDefinition*)resourceManager->GetResource(SHIP, WARBIRD)->texture]
    //hardcoding in values for now

    i = 0;
    for(std::map<int, GameObject>::iterator it = objectlist.begin(); it != objectlist.end(); ++it)
    {
    	GameObject *gob = &(it->second);
    	if (gob->text.compare("exhaust.bmp") == 0)
    	{
    		string q = gob->text;
    		q = "";
    	}
		renderList[i].texture = textures[gob->text];
		renderList[i].texOffsetX = gob->animeImage->getLeftOffSet();
		renderList[i].texOffsetY = gob->animeImage->getTopOffSet();
		renderList[i].objectHeight = gob->animeImage->getBottomOffSet();
		renderList[i].objectWidth = gob->animeImage->getRightOffSet();
		renderList[i].rotation = it->second.angle * 2;
		renderList[i].objectHeightPx = gob->animeImage->getHeight();
		renderList[i].objectWidthPx = gob->animeImage->getWidth();

        renderList[i].x = SCRCENTREW + (it->second.position.x() - xOffset);
        renderList[i].y = SCRCENTREH + (it->second.position.y() - yOffset);

        renderList[i].textX = SCRCENTREW + (it->second.position.x() - xOffset);
        renderList[i].textY = SCRCENTREH - (it->second.position.y() - yOffset);
        renderList[i].name = it->second.owner;
        i++;
    }
    renderCount = i;
}


void Renderer::Initialize()
{
    renderCount = 0;
    makeCurrent();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    QDir dir(":/textures/");
    QFileInfoList list = dir.entryInfoList();
    for(int i = 0; i < list.size(); i++)
    {
        QFileInfo fileInfo = list.at(i);
        QPixmap pix;
        QString sfx = fileInfo.completeSuffix();
        if(fileInfo.completeSuffix()=="png")
        {
            pix = QPixmap(fileInfo.filePath(), "PNG");
        }
        else
        {
            pix = QPixmap(fileInfo.filePath(), "BMP");
            QBitmap bmp = pix.createMaskFromColor(QColor(0,0,0), Qt::MaskOutColor);
            pix.setAlphaChannel(bmp);
        }
        GLuint texture = bindTexture(pix, GL_TEXTURE_2D, GL_RGBA, QGLContext::InvertedYBindOption);
        textures.insert(std::pair<std::string, GLuint>(fileInfo.fileName().toStdString(), texture));
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Renderer::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble) h);
}

void Renderer::Render()
{
	QFont font("Helvetica", 8);
    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    for(int i = 0; i < renderCount; i++)
	{
		QMatrix3x4 quad;

		//set the 4 points of the ship
		//bottom left
		quad(0,0) = renderList[i].x;
		quad(0,1) = renderList[i].y;
		quad(0,2) = 1;
		//bottom right
		quad(1,0) = renderList[i].objectWidthPx + renderList[i].x;
		quad(1,1) = renderList[i].y;
		quad(1,2) = 1;
		//top right
		quad(2,0) = renderList[i].objectWidthPx + renderList[i].x;
		quad(2,1) = renderList[i].objectHeightPx + renderList[i].y;
		quad(2,2) = 1;
		//top left
		quad(3,0) = renderList[i].x;
		quad(3,1) = renderList[i].objectHeightPx + renderList[i].y;
		quad(3,2) = 1;

		if (renderList[i].name != "")
			renderText(renderList[i].textX - 5, renderList[i].textY - 35, renderList[i].name, font);

		if(renderList[i].rotation > 0)//skip all this if the object is rotationless or at 0;
		{
			int centerx = (quad(0,0) + quad(2,0)) / 2;
			int centery = (quad(0,1) + quad(2,1)) / 2;

			//set up translation to origin
			QMatrix3x3 cTrans;
			cTrans(2,0) = -centerx;
			cTrans(2,1) = -centery;

			//setup the rotation matrix
			QMatrix3x3 rot;
			rot(0,0) = cos(DEGTORAD(renderList[i].rotation));
			rot(0,1) = sin(DEGTORAD(renderList[i].rotation));
			rot(1,0) = -sin(DEGTORAD(renderList[i].rotation));
			rot(1,1) = cos(DEGTORAD(renderList[i].rotation));

			//set up translation to initial point
			QMatrix3x3 transUndo;
			transUndo(2,0) = centerx;
			transUndo(2,1) = centery;

			cTrans = cTrans * rot;
			cTrans = cTrans * transUndo;
			quad = quad * cTrans;
        }

        glBindTexture(GL_TEXTURE_2D, renderList[i].texture);

        glBegin(GL_QUADS);//begin points
            glTexCoord2f(renderList[i].texOffsetX, renderList[i].texOffsetY); glVertex2f(quad(0,0), quad(0,1));
            glTexCoord2f(renderList[i].texOffsetX+renderList[i].objectWidth, renderList[i].texOffsetY); glVertex2f(quad(1,0), quad(1,1));
            glTexCoord2f(renderList[i].texOffsetX+renderList[i].objectWidth, renderList[i].texOffsetY+renderList[i].objectHeight); glVertex2f(quad(2,0), quad(2,1));
            glTexCoord2f(renderList[i].texOffsetX, renderList[i].texOffsetY+renderList[i].objectHeight); glVertex2f(quad(3,0), quad(3,1));
        glEnd();
    }
        glBindTexture(GL_TEXTURE_2D, textures["chatbox.png"]);
        glBegin(GL_QUADS);
            glTexCoord2f(0,0);      glVertex2f(0,0);
            glTexCoord2f(1,0);  glVertex2f(600, 0);
            glTexCoord2f(1,1);  glVertex2f(600, 200);
            glTexCoord2f(0,1);      glVertex2f(0, 200);
        glEnd();
        glFlush();
        glDisable(GL_TEXTURE_2D);
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

