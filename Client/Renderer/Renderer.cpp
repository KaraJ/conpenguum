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
#include <iostream>
#include <iomanip>
#include "../../Core/resourceMgr/resourceEnums.h"

using namespace std;

Renderer::Renderer(QWidget *parent,std::map<int, GameObject> &gameSt, std::deque<QString> *chatText, QString* localText) :
		QGLWidget(QGLFormat(QGL::SampleBuffers|QGL::AlphaChannel), parent), objectlist(gameSt), chatText_(chatText), localText_(localText), deathTime_(0)
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

    std::vector<MapTile*> &tiles = map->getTiles();
    for(i = 0; i < tiles.size(); i++)
    {
        ResourceManager * rm = ResourceManager::GetInstance();
        TexturedResourceDefinition *rd = (TexturedResourceDefinition*)rm->GetResource(TILE, tiles[i]->getTileID());

        renderList[i].texture = textures[rd->texture];
        renderList[i].texOffsetX = rd->texture_xoffset;
        renderList[i].texOffsetY = rd->texture_yoffset;
        renderList[i].objectHeight = rd->texture_height;
        renderList[i].objectWidth = rd->texture_width;
        renderList[i].rotation = 0;
        renderList[i].objectHeightPx = rd->object_height;
        renderList[i].objectWidthPx = rd->object_width;
        renderList[i].objectId = -1;

        renderList[i].x = SCRCENTREW + (tiles[i]->getPos().x() - xOffset);// - rd->object_width/2;
        renderList[i].y = SCRCENTREH + (tiles[i]->getPos().y() - yOffset);// - rd->object_height/2;
    }
    mapTileCount = i;

    for(std::map<int, GameObject>::iterator it = objectlist.begin(); it != objectlist.end(); ++it)
    {
    	GameObject *gob = &(it->second);
    	int scale = 1;
    	if (gob->health == -1)
    	{
    		if (gob->shield > 5)
    			scale = 10;
    		else if (gob->shield > 3)
    			scale = 5;
    		else if (gob->shield > 0)
    			scale = 2;
    	}

    	renderList[i].texture = textures[gob->textureName];
        renderList[i].texOffsetX = gob->animeImage->getLeftOffSet();
        renderList[i].texOffsetY = gob->animeImage->getTopOffSet();
        renderList[i].objectHeight = gob->animeImage->getBottomOffSet() - gob->animeImage->getTopOffSet();
        renderList[i].objectWidth = gob->animeImage->getRightOffSet() - gob->animeImage->getLeftOffSet();
        renderList[i].rotation = it->second.angle * 2;
        renderList[i].objectHeightPx = gob->objHeight * scale;
        renderList[i].objectWidthPx = gob->objWidth * scale;

        renderList[i].x = SCRCENTREW + (gob->position.x() - xOffset) - (gob->objWidth * scale) / 2;
        renderList[i].y = SCRCENTREH + (gob->position.y() - yOffset) - (gob->objHeight * scale) / 2;

        renderList[i].textX = SCRCENTREW + (it->second.position.x() - xOffset);
        renderList[i].textY = SCRCENTREH - (it->second.position.y() - yOffset);
        renderList[i].health = it->second.health;
        renderList[i].shield = it->second.shield;
        renderList[i].name = it->second.owner;
        renderList[i].objectId = it->second.objectId;
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

void Renderer::loadMap(Map *map)
{
    this->map = map;
}

void Renderer::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble) h);
}

void Renderer::Render(int clientId, const vector<Player> &playerList)
{
	QFont nameFont("Helvetica", 8);
	QFont healthFont("Comic Sans MS", 10, 75);
	QFont deathFont("Helvetica", 20, 85);
	QFont chatFont("Comic Sans MS", 8, 75);

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

		float hp = (float)renderList[i].health / 100;
		float sh = (float)renderList[i].shield / 100;
		if (renderList[i].objectId == clientId)
		{
			std::string str = renderList[i].name.toStdString();
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
		else if (renderList[i].name != "")// draw little health & shield bars on other ships
		{
			glBindTexture(GL_TEXTURE_2D, textures["shieldbar.bmp"]);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);  glVertex2f(quad(0,0) + 10, quad(0,1) - 5);
				glTexCoord2f(1,0);  glVertex2f(quad(0,0) + 30*sh + 10, quad(0,1) - 5);
				glTexCoord2f(1,1);  glVertex2f(quad(0,0) + 30*sh + 10, quad(0,1) - 8);
				glTexCoord2f(0,1);  glVertex2f(quad(0,0) + 10, quad(0,1) -8);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, textures["healthbar.bmp"]);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);  glVertex2f(quad(0,0) + 10, quad(0,1) - 8);
				glTexCoord2f(1,0);  glVertex2f(quad(0,0) + 30*hp + 10, quad(0,1) - 8);
				glTexCoord2f(1,1);  glVertex2f(quad(0,0) + 30*hp + 10, quad(0,1) - 11);
				glTexCoord2f(0,1);  glVertex2f(quad(0,0) + 10, quad(0,1) -11);
			glEnd();
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
    if (--deathTime_ > 0)
	{
		qglColor(Qt::red);
		renderText(SCREENWIDTH/2 - 100, SCREENHEIGHT/2, "You lost The Game", deathFont);
		ostringstream oss;
		oss << "Respawning in " << fixed << setprecision(1) << ((float)deathTime_/30) << " seconds";
		renderText(SCREENWIDTH/2 - 145, SCREENHEIGHT/2 + 25, QString(oss.str().c_str()), deathFont);
		qglColor(Qt::white);
	}
    RenderScores(playerList);

    //render chat messages
	qglColor(Qt::yellow);
	int linePos = 1;
	deque<QString>::iterator it;
	for (it = chatText_->begin(); it != chatText_->end(); it++)
	{
		renderText(5, SCREENHEIGHT - 20*linePos - 5, *it, chatFont);
		if (++linePos == MAXCHATLINES + 1)
			linePos = 1;
	}
	renderText(5, SCREENHEIGHT - 5, *localText_, chatFont);
	qglColor(Qt::white);

	glBindTexture(GL_TEXTURE_2D, textures["chatbox.png"]);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);  glVertex2f(0,0);
		glTexCoord2f(1,0);  glVertex2f(510, 0);
		glTexCoord2f(1,1);  glVertex2f(510, 180);
		glTexCoord2f(0,1);  glVertex2f(0, 180);
	glEnd();

	glFlush();
	glDisable(GL_TEXTURE_2D);
    updateGL();
}

void Renderer::RenderScores(const std::vector<Player> &playerList)
{
	QFont scoreFont("Helvetica", 8);
	int lines = 0;
	for (size_t i = 0; i < playerList.size(); i++)
	{
		ostringstream oss;
		renderText(SCREENWIDTH - 225, SCREENHEIGHT - 20*lines - 15, QString(playerList[i].getName().c_str()), scoreFont);
		oss << playerList[i].getKills();
		renderText(SCREENWIDTH - 140, SCREENHEIGHT - 20*lines - 15, QString::fromStdString(oss.str()), scoreFont);
		oss.str(""); oss << playerList[i].getDeaths();
		renderText(SCREENWIDTH - 95, SCREENHEIGHT - 20*lines - 15, QString::fromStdString(oss.str()), scoreFont);
		oss.str(""); oss << playerList[i].getStreak();
		renderText(SCREENWIDTH - 50, SCREENHEIGHT - 20*lines++ - 15, QString::fromStdString(oss.str()), scoreFont);
	}
	renderText(SCREENWIDTH - 225, SCREENHEIGHT - 20*lines - 15, "Player Name", scoreFont);
	//qglColor(Qt::green);
	renderText(SCREENWIDTH - 140, SCREENHEIGHT - 20*lines - 15, "Kills", scoreFont);
	//qglColor(Qt::red);
	renderText(SCREENWIDTH - 95, SCREENHEIGHT - 20*lines - 15, "Deaths", scoreFont);
	//qglColor(Qt::blue);
	renderText(SCREENWIDTH - 50, SCREENHEIGHT - 20*lines++ - 15, "Streak", scoreFont);
	renderText(SCREENWIDTH - 160, SCREENHEIGHT - 20*lines - 25, "- Score Board -", scoreFont);
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

