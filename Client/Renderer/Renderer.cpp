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
    resourceManager = ResourceManager::GetInstance();
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
    	TexturedResourceDefinition *rd;

    	if (gob->objectId < MAX_CLIENTS)
    		rd = (TexturedResourceDefinition*)resourceManager->GetResource(SHIP, 0);
    	else if (gob->objectId == 500)
    	{
    		rd = (TexturedResourceDefinition*)resourceManager->GetResource(AIDBOX, 0);
    		renderList[i].texture = textures["firstaid.bmp"];
			renderList[i].texOffsetX = 0;
			renderList[i].texOffsetY = 0;
			renderList[i].objectHeight = 1;
			renderList[i].objectWidth = 1;
			renderList[i].rotation = 0;
			renderList[i].objectHeightPx = rd->object_width;
			renderList[i].objectWidthPx = rd->object_height;
			renderList[i].x = SCRCENTREW + (gob->position.x() - xOffset) - rd->object_width / 2;
			renderList[i].y = SCRCENTREH + (gob->position.y() - yOffset) - rd->object_height / 2;
			i++;
			continue;
    	}
    	else if (gob->objectId > MAX_CLIENTS && gob->objectId < MAX_REAL_OBJECT)
    		rd = (TexturedResourceDefinition*)resourceManager->GetResource(SHOT, 0);
    	else
    		rd = (TexturedResourceDefinition*)resourceManager->GetResource(EXHAUST, 0);

    	renderList[i].texture = textures[rd->texture];
		renderList[i].texOffsetX = gob->animeImage->getLeftOffSet();
		renderList[i].texOffsetY = gob->animeImage->getTopOffSet();
		renderList[i].objectHeight = gob->animeImage->getBottomOffSet() - gob->animeImage->getTopOffSet();
		renderList[i].objectWidth = gob->animeImage->getRightOffSet() - gob->animeImage->getLeftOffSet();
		renderList[i].rotation = it->second.angle * 2;
		renderList[i].objectHeightPx = rd->object_width;
		renderList[i].objectWidthPx = rd->object_height;

        renderList[i].x = SCRCENTREW + (gob->position.x() - xOffset) - rd->object_width / 2;
        renderList[i].y = SCRCENTREH + (gob->position.y() - yOffset) - rd->object_height / 2;

        renderList[i].textX = SCRCENTREW + (it->second.position.x() - xOffset);
        renderList[i].textY = SCRCENTREH - (it->second.position.y() - yOffset);
        renderList[i].health = it->second.health;
        renderList[i].shield = it->second.shield;
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
	QFont nameFont("Helvetica", 8);
	QFont healthFont("Comic Sans MS", 10, 75);
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
			renderText(renderList[i].textX - 5, renderList[i].textY - 20, renderList[i].name, nameFont);

		if (renderList[i].health != -1 && renderList[i].name != "")
		{
			std::string str = renderList[i].name.toStdString();
			float hp = (float)renderList[i].health / 100;
			float sh = (float)renderList[i].shield / 100;
			renderText(20, 18, "Health", healthFont);

			glBindTexture(GL_TEXTURE_2D, textures["healthbar.bmp"]);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);  glVertex2f(20, SCREENHEIGHT - 35);
				glTexCoord2f(1,0);  glVertex2f(20 + 100*hp, SCREENHEIGHT - 35);
				glTexCoord2f(1,1);  glVertex2f(20 + 100*hp, SCREENHEIGHT - 50);
				glTexCoord2f(0,1);  glVertex2f(20, SCREENHEIGHT - 50);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, textures["shieldbar.bmp"]);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);  glVertex2f(20, SCREENHEIGHT - 20);
				glTexCoord2f(1,0);  glVertex2f(20 + 100*sh, SCREENHEIGHT - 20);
				glTexCoord2f(1,1);  glVertex2f(20 + 100*sh, SCREENHEIGHT - 35);
				glTexCoord2f(0,1);  glVertex2f(20, SCREENHEIGHT - 35);
			glEnd();

			ostringstream oss;
			int totalHp = renderList[i].health + renderList[i].shield;
			if (totalHp <= 0)
			{
				renderText(35, 40, "Dead yo", healthFont);
			}
			else
			{
				oss <<  renderList[i].shield << " / 100";
				if (renderList[i].shield > 50)
					qglColor(Qt::blue);
				else
					qglColor(Qt::white);
				renderText(40, 33, QString(oss.str().c_str()), healthFont);
				oss.str("");
				oss <<  renderList[i].health << " / 100";
				if (renderList[i].health > 70)
					qglColor(Qt::white);
				else if (renderList[i].health > 40)
					qglColor(Qt::yellow);
				else
					qglColor(Qt::red);
				renderText(40, 48, QString(oss.str().c_str()), healthFont);
			}
			qglColor(Qt::white);
		}

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
		glTexCoord2f(0,0);  glVertex2f(0,0);
		glTexCoord2f(1,0);  glVertex2f(600, 0);
		glTexCoord2f(1,1);  glVertex2f(600, 200);
		glTexCoord2f(0,1);  glVertex2f(0, 200);
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

