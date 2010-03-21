#include "Renderer.h"
#include <QtGlobal>
#include <QPainter>
#include <QtGui>
#include <QGLWidget>
#include <QtOpenGL>
#include <cmath>
#include <cassert>
#include "../../Core/resourceMgr/resourceEnums.h"

using namespace std;

Renderer::Renderer(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers|QGL::AlphaChannel), parent)
{
    resourceManager = ResourceManager::GetInstance();
    Initialize();
}

void Renderer::LoadTextures()
{
	// loading all the textures into the map.
	string str;
	ResourceDefinition* rd;
	GLuint texture;

	for(size_t i = 0; i < NUMRESOURCETYPES; i++)
	{
		if(i == SHIP){
			rd = (ShipDefinition*)resourceManager->GetResource(i, i);
			str = ":/textures/" + ((ShipDefinition*)rd)->texture;
		}
		else if(i == SHOT) {
			rd = (ShotDefinition*)resourceManager->GetResource((RESOURCETYPES)i, (SHOTTYPES)i);
			str = ":/textures/" + ((ShotDefinition*)rd)->texture;
		}

		texture = bindTexture(QPixmap(QString::fromStdString(str), "BMP"), GL_TEXTURE_2D);
		//textures.insert(pair<string, GLuint>(str, texture));
		textures.insert(pair<string, ResourceDefinition*>(str, rd));
	}

	return;
    //    textures[0] = bindTexture(QPixmap(QString(":/textures/ships.bmp"),"BMP"), GL_TEXTURE_2D);
    //texture = bindTexture(QPixmap(":/textures/bullets.bmp", "BMP"), GL_TEXTURE_2D);
    //textures.insert(std::pair<std::string, GLuint>("bullets.bmp", texture));
    //texture = bindTexture(QPixmap(":/textures/bg01.bmp", "BMP"), GL_TEXTURE_2D);
    //textures.insert(std::pair<std::string, GLuint>("bg01.bmp", texture));

}

void Renderer::buildRenderList(vector<UpdateObject> objectlist)
{
    //if we have more than 40k render objects, we're fucked.
    assert(MAXRENDERCOUNT > objectlist.size()/*+map objects*/);

    size_t i, xOffset, yOffset;

    //grab the first render object, this should be the client's ship, and thus our center
    xOffset = SCRCENTREW - objectlist[0].getPos().x();
    yOffset = SCRCENTREH - objectlist[0].getPos().y();

    //sample code for getting a texture from resource manager
    //you need to know the type of the resource you are getting, so you can
    //properly cast to the correct struct type
    //textures[(ShipDefinition*)resourceManager->GetResource(SHIP, WARBIRD)->texture];
    //hardcoding in values for now
    LoadTextures(); // loading textures.

    // we now have textures so lets use them to build the renderlist.
    map<string, ResourceDefinition*>::iterator it; // will be used for going through the list.
    size_t loadCount = 0;
    ResourceDefinition* rd;
    for(it = textures.begin(); it != textures.end(); ++it)
    {
    	rd = (ResourceDefinition*)(it->second);
    	renderList[loadCount].texture = rd->textureLocation;
		renderList[loadCount].texOffsetX = rd->texture_xoffset;
		renderList[loadCount].texOffsetY = rd->texture_yoffset;
		renderList[loadCount].objectHeight = rd->object_height;
		renderList[loadCount].objectWidth = rd->object_width;
    	if(rd->id == SHIP)
    	{
    		renderList[loadCount].x = objectlist[0].getPos().x() + xOffset;
    		renderList[loadCount].y = objectlist[0].getPos().y() + yOffset;
    		renderList[loadCount].rotation = objectlist[0].getRotation() * 2; //** HARDCODED FOR NOW
    		renderList[loadCount].objectHeightPx = 50;
    		renderList[loadCount].objectWidthPx = 50;

    	} else if(rd->id == SHOT)
    	{
    		renderList[loadCount].objectHeightPx=16;
    		renderList[loadCount].objectWidthPx=16;

    	}
    	loadCount++;
    }



    /*renderList[0].texture = textures["ships.bmp"];
    renderList[0].x = objectlist[0].getPos().x() + xOffset;
    renderList[0].y = objectlist[0].getPos().y() + yOffset;
    renderList[0].rotation = objectlist[0].getRotation() * 2;
    renderList[0].texOffsetX = 0;
    renderList[0].texOffsetY = 3 / 32.0;
    renderList[0].objectHeight = 1 / 32.0;
    renderList[0].objectWidth = 1 / 10.0;
    renderList[0].objectHeightPx = 50;
    renderList[0].objectWidthPx = 50;

    for(i = 1; i < objectlist.size(); i++)
    {
        if(objectlist[i].getObjectId() == 32) //TODO: Hard coded for testing, BULLET
        	{
            renderList[i].texture = textures["bullets.bmp"];
            renderList[i].texOffsetY = 0;
            renderList[i].objectHeight = 1 / 10.0;
            renderList[i].objectWidth = 1 / 4.0;
            renderList[i].rotation = 0;
            renderList[i].objectHeightPx=16;
            renderList[i].objectWidthPx=16;
        }
        else if(objectlist[i].getObjectId() == 33) //TODO: Hard coded for testing, WALL
        {
            renderList[i].texture = textures["bg01.bmp"];
            renderList[i].texOffsetY = 0;
            renderList[i].objectHeight = 1;
            renderList[i].objectWidth = 1;
            renderList[i].rotation = 0;
            renderList[i].objectHeightPx = 25;
            renderList[i].objectWidthPx = 25;
        }
        else
        {
            renderList[i].texture = textures["ships.bmp"];
            renderList[i].texOffsetY = 3 / 32.0;
            renderList[i].objectHeight = 1 / 32.0;
            renderList[i].objectWidth = 1 / 10.0;
            renderList[i].rotation = objectlist[i].getRotation() * 2;
            renderList[i].objectHeightPx = 50;
            renderList[i].objectWidthPx = 50;
        }

        renderList[i].texOffsetX = 0;
        renderList[i].x = xOffset + objectlist[i].getPos().x();
        renderList[i].y = yOffset + objectlist[i].getPos().y();
    }
    */
    //renderCount = i;
    renderCount = loadCount;
}


void Renderer::Initialize()
{
    renderCount = 0;
    makeCurrent();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

	LoadTextures();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Renderer::resizeGL(int w, int h)
{
    glViewport(0,0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-3.6f);
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble) h );
}

void Renderer::Render()
{
    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    //glBindTexture(GL_TEXTURE_2D, texName);

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
        if(renderList[i].rotation > 0)//skip all this if the object is rotationless or at 0;
        {
            //set up translation to origin
        	QMatrix3x3 translate;
        	translate(2,0) = -renderList[i].x;
        	translate(2,1) = -renderList[i].y;

            //setup the rotation matrix
        	QMatrix3x3 rot;
            rot(0,0) = cos(DEGTORAD(renderList[i].rotation));
            rot(0,1) = sin(DEGTORAD(renderList[i].rotation));
            rot(1,0) = -sin(DEGTORAD(renderList[i].rotation));
            rot(1,1) = cos(DEGTORAD(renderList[i].rotation));

            translate = translate * rot;
            translate(2,0) = renderList[i].x;
            translate(2,1) = renderList[i].y;

            quad = quad * translate;
        }

        glBindTexture(GL_TEXTURE_2D, renderList[i].texture);

        glBegin(GL_QUADS);//begin points
            glTexCoord2f(renderList[i].texOffsetX, renderList[i].texOffsetY); glVertex2f(quad(0,0), quad(0,1));
            glTexCoord2f(renderList[i].texOffsetX+renderList[i].objectWidth, renderList[i].texOffsetY); glVertex2f(quad(1,0), quad(1,1));
            glTexCoord2f(renderList[i].texOffsetX+renderList[i].objectWidth, renderList[i].texOffsetY+renderList[i].objectHeight); glVertex2f(quad(2,0), quad(2,1));
            glTexCoord2f(renderList[i].texOffsetX, renderList[i].texOffsetY+renderList[i].objectHeight); glVertex2f(quad(3,0), quad(3,1));
        glEnd();
    }

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
