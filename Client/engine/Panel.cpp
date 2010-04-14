/*----------------------------------------------------------------------------
--  SOURCE FILE: panel.cpp
--
--  PROGRAM:
--
--
--  FUNCTIONS:
--      void keyPressEvent          (QKeyEvent *event);
--      void resizeEvent            (QResizeEvent *event);
--      void updateSelectionStep    (qreal val);
--      void updateFlipStep         (qreal val);
--      void flip                   ();
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  NOTES:
--      The panel which is drawn on the screen that holds all the menu items.
----------------------------------------------------------------------------*/

#ifndef QT_NO_OPENGL
#include <QtOpenGL/QtOpenGL>
#else
#endif
#include <QtGui/QtGui>
#include "Panel.h"
#include "Roundrectitem.h"
#include "Splashitem.h"
#include "ui_backside.h"
#include <math.h>
#include "BaseWindow.h"
#include "../../Core/ConfigParser.h"
#include "ipbox.h"
#include "connectthread.h"
#include <map>
using namespace std;
/*--------------------------------------------------------------------------------------
--  Function: Panel
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: Panel::Panel()
--
--  RETURNS: a new panel
--
--  Notes:
--      The panel is the main menu that the user will see on the screen.
--------------------------------------------------------------------------------------*/
Panel::Panel() : selectedX(0), selectedY(0), width(1), height(3), flipped(false), flipLeft(true)
{
    Phonon::MediaObject *startupMusic =
        Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource("Resources/sounds/startup.wav"));
    startupMusic->play();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(FullViewportUpdate);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    setBackgroundBrush(QPixmap(":/images/stars.gif"));

#ifndef QT_NO_OPENGL
    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
#endif

    setMinimumSize(1024, 768);

    selectionTimeLine = new QTimeLine(150, this); // speed of selection movement.
    flipTimeLine = new QTimeLine(500, this);

    // for menu buttons
    QRectF bounds((-width / 2.0) * 150, (-height / 2.0) * 150, width * 150, height * 150);
    QRectF bounds2((-width / 2.0) * 350, (-height / 2.0) * 13, width * 350, height * 70);
    QRectF settingsBaseBounds(-100, -80, 200, 200);
    scene = new QGraphicsScene(bounds, this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(scene);

    // menu background bounding box
    baseItem = new RoundRectItem(bounds2, QColor(255, 255, 255, 65));
    scene->addItem(baseItem);
    // settings background bounding box
    settingBaseItem = new RoundRectItem(settingsBaseBounds, QColor(255, 255, 255, 65));
    settingBaseItem->setVisible(false);
	scene->addItem(settingBaseItem);

    // settings box
    QWidget *embed = new QWidget;
    ui = new Ui_BackSide;
    ui->setupUi(embed);
    selectedShip = "wbship";
    QObject::connect(ui->ship1b, SIGNAL(clicked()), this, SLOT(b1Clicked()));
	QObject::connect(ui->ship2b, SIGNAL(clicked()), this, SLOT(b2Clicked()));
	QObject::connect(ui->ship3b, SIGNAL(clicked()), this, SLOT(b3Clicked()));
	QObject::connect(ui->ship4b, SIGNAL(clicked()), this, SLOT(b4Clicked()));
	QObject::connect(ui->ship5b, SIGNAL(clicked()), this, SLOT(b5Clicked()));
	QObject::connect(ui->ship6b, SIGNAL(clicked()), this, SLOT(b6Clicked()));
	QObject::connect(ui->ship7b, SIGNAL(clicked()), this, SLOT(b7Clicked()));
	QObject::connect(ui->ship8b, SIGNAL(clicked()), this, SLOT(b8Clicked()));

    //ui->comboBox->setFocus();
    backItem = new RoundRectItem(settingsBaseBounds, embed->palette().window(), embed);
    backItem->setTransform(QTransform().rotate(180, Qt::YAxis));
    backItem->setParentItem(settingBaseItem);

    // for highlighter
    selectionItem = new RoundRectItem(QRectF(-158, -33, 320, 65), Qt::blue);
    selectionItem->setParentItem(baseItem);
    selectionItem->setZValue(-1);
    selectionItem->setPos(posForLocation(0, 0));
    startPos = selectionItem->pos();

    grid = new QGraphicsItem **[height];

    for (int y = 0; y < height; ++y)
    {
        grid[y] = new QGraphicsItem *[width];

        for (int x = 0; x < width; ++x)
        {
            // for each menu item
            RoundRectItem *item = new RoundRectItem(QRectF(-154, -30, 308, 58),
                                                    QColor(255, 255, 255, 28));
            item->setPos(posForLocation(x, y));

            item->setParentItem(baseItem);
            item->setFlag(QGraphicsItem::ItemIsFocusable);
            grid[y][x] = item;
            if(y == 3)
                break;

            switch (y)
            {
            case 0:
                item->setPixmap(QPixmap(":/images/start.png"));
                break;
            case 1:
                item->setPixmap(QPixmap(":/images/ships.png"));
                break;
            case 2:
                item->setPixmap(QPixmap(":/images/quit.png"));
                break;
            default:
                break;
            }

            connect(item, SIGNAL(activated()), this, SLOT(flip()));
        }
    }

    grid[0][0]->setFocus();

    connect(backItem, SIGNAL(activated()), this, SLOT(flip()));
    connect(selectionTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(updateSelectionStep(qreal)));
    connect(flipTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(updateFlipStep(qreal)));

    splash = new SplashItem;
    splash->setZValue(1);
    splash->setPos(-splash->rect().width() / 2, scene->sceneRect().top());
    scene->addItem(splash);
    splash->hide();
    //splash->grabKeyboard();

    updateSelectionStep(0);

    mbox.setWindowTitle("Connecting");
	mbox.setText("Attempting to connect to server...");
	mbox.setStandardButtons(0);

    //setWindowTitle(tr("Conpenguum Main Menu"));
}


/*--------------------------------------------------------------------------------------
--  Function: ~Panel
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: Panel::~Panel()
--
--  RETURNS: nothing, it's a destructor
--
--  Notes:
--      Destructor to destroy the panel.
--------------------------------------------------------------------------------------*/
Panel::~Panel()
{
    for(int y = 0; y < height; ++y)
        delete [] grid[y];
    delete [] grid;
}



/*--------------------------------------------------------------------------------------
--  Function: keyPressEvent
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: void Panel::keyPressEvent(QKeyEvent *event)
--      event - holds the information for the event
--
--  RETURNS: void
--
--  Notes:
--      Controls what happens when the arrow keys or enter is pressed.
--------------------------------------------------------------------------------------*/
void Panel::keyPressEvent(QKeyEvent *event)
{
    if (splash->isVisible() || event->key() == Qt::Key_Return || flipped) {
        QGraphicsView::keyPressEvent(event);
        return;
    }

    selectedX = (selectedX + width + (event->key() == Qt::Key_Right) - (event->key() == Qt::Key_Left)) % width;
    selectedY = (selectedY + height + (event->key() == Qt::Key_Down) - (event->key() == Qt::Key_Up)) % height;
    grid[selectedY][selectedX]->setFocus();

    selectionTimeLine->stop();
    startPos = selectionItem->pos();
    endPos = posForLocation(selectedX, selectedY);
    selectionTimeLine->start();
}


/*--------------------------------------------------------------------------------------
--  Function: resizeEvent
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: void Panel::resizeEvent(QResizeEvent *event)
--      event - holds the information for the event
--
--  RETURNS: void
--
--  Notes:
--      If the window is resized, handles positioning of main menu in center of screen.
--------------------------------------------------------------------------------------*/
void Panel::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}


/*--------------------------------------------------------------------------------------
--  Function: updateSelectionStep
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: void Panel::updateSelectionStep(qreal val)
--      val - the starting item position
--
--  RETURNS: void
--
--  Notes:
--      basically needed for initialization of the "menu angle" timeline.
--------------------------------------------------------------------------------------*/
void Panel::updateSelectionStep(qreal val)
{
    QPointF newPos(startPos.x() + (endPos - startPos).x() * val,
                   startPos.y() + (endPos - startPos).y() * val);
    selectionItem->setPos(newPos);

    QTransform transform;
    yrot = newPos.x() / 6.0;
    xrot = newPos.y() / 6.0;
    transform.rotate(newPos.x() / 6.0, Qt::YAxis);
    transform.rotate(newPos.y() / 6.0, Qt::XAxis);
    baseItem->setTransform(transform);
}


/*--------------------------------------------------------------------------------------
--  Function: updateFlipStep
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: void Panel::updateFlipStep(qreal val)
--      val - the starting item position
--
--  RETURNS: void
--
--  Notes:
--      Needed for initialization of the "accept/flip" timeline.
--------------------------------------------------------------------------------------*/
void Panel::updateFlipStep(qreal val)
{
    settingBaseItem->setVisible(true);
    qreal finalxrot = xrot - xrot * val;
    qreal finalyrot;
    if(flipLeft)
    {
        finalyrot = yrot - yrot * val - 180 * val;
    }
    else
    {
        finalyrot = yrot - yrot * val + 180 * val;
    }
    QTransform transform;
    transform.rotate(finalyrot, Qt::YAxis);
    transform.rotate(finalxrot, Qt::XAxis);
    qreal scale = 1 - sin(3.14 * val) * 0.3;
    transform.scale(scale, scale);
    settingBaseItem->setTransform(transform);
    if(val == 0)
    {
        grid[selectedY][selectedX]->setFocus();
        settingBaseItem->setVisible(false);
    }
}


/*--------------------------------------------------------------------------------------
--  Function: flip
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: void Panel::flip()
--
--  RETURNS: void
--
--  Notes:
--      Actually does the animation of the "flipping menu" for the settings page.
--------------------------------------------------------------------------------------*/
void Panel::flip()
{
    if (flipTimeLine->state() == QTimeLine::Running)
        return;

    if (flipTimeLine->currentValue() == 0)
    {
        switch(selectedY)
        {
        // play
        case 0:
        {
			ConfigParser cp;
			map<string, string> params;
			IpBox *ipbox;

			if (cp.Parse("client.conf", params)
					&& params.find("username") != params.end()
					&& params.find("server_ip") != params.end()
					&& params.find("tcp_port") != params.end())
			{
				QString cheat = ui->cheatEntry->text();

				if(cheat == "Aman")
				{
					selectedShip = "adminship";
				}
				cerr << selectedShip.c_str();
				ipbox = new IpBox(this, params["username"], params["server_ip"], params["tcp_port"]);
				ipbox->exec();
				if (ipbox->result() == 0)
				{
					delete ipbox;
					return;
				}

				cerr << "\nname: " << ipbox->getName() << "\nip: " << ipbox->getIp() << "\nport: " << ipbox->getPort() << endl;
				ConnectThread *thread = new ConnectThread(ipbox->getName(), ipbox->getIp(), ipbox->getPort(), selectedShip);
				QObject::connect(thread, SIGNAL(serverConnect(int)), this, SLOT(serverConnect(int)));
				QObject::connect(thread, SIGNAL(errorConnect()), this, SLOT(errorConnect()));
				QObject::connect(thread, SIGNAL(nameInUse()), this, SLOT(nameInUse()));
				QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));


				delete ipbox;
				thread->start();
				mbox.show();
			}
			else
				cerr << "Invalid configuration file." << endl;

			return;
		}

        // settings
        case 1:
            break;

        // quit
        case 2:
            // need to replace with an engine quit... will tell everything to quit();
            this->destroy(true, false);
            exit(0);
            return;
        }

        flipTimeLine->setDirection(QTimeLine::Forward);
        flipTimeLine->start();
        flipped = true;
        flipLeft = selectionItem->pos().x() < 0;
    }
    else
    {
        flipTimeLine->setDirection(QTimeLine::Backward);
        flipTimeLine->start();
        flipped = false;
    }
}

void Panel::serverConnect(int clientId)
{
	mbox.hide();
	BaseWindow* bw = new BaseWindow();
	bw->Start(clientId);
	this->hide();
}

void Panel::errorConnect()
{
	mbox.hide();
	QMessageBox::warning(this, "Connection Error", "Cannot connect to server", 1, 0, 0);
}

void Panel::nameInUse()
{
	mbox.hide();
	QMessageBox::warning(this, "Connection Error", "Username is already in use", 1, 0, 0);
}

/*--------------------------------------------------------------------------------------
--  Function: posForLocation
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: QPointF Panel::posForLocation(int x, int y) const
--      x - the x value of the item
--      y - the y value of the item
--
--  RETURNS: QPointF - the point for the location of the current item
--
--  Notes:
--      Gives the screen point for the item you choose.
--------------------------------------------------------------------------------------*/
QPointF Panel::posForLocation(int x, int y) const
{
    return QPointF(x * 65, y * 65)
        - QPointF((width - 1) * -10, (height - 1) * -10);
}

/*--------------------------------------------------------------------------------------
--  Function: closeEvent
--
--  DATE: Mar 20, 2010
--
--  DESIGNER: Daraius Dastoor
--
--  PROGRAMMER REVISIONS: Daraius Dastoor & Ben Learn
--
--  INTERFACE: void Panel::closeEvent(QCloseEvent * e)
--      e - the event to close!
--
--  RETURNS: Naw
--
--  Notes:
--      To override the "X" button close event.
--------------------------------------------------------------------------------------*/
void Panel::closeEvent(QCloseEvent * e)
{
	//this->destroy(true, false);
	exit(0);
}
