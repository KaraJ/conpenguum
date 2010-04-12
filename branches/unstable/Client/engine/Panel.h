/*----------------------------------------------------------------------------
--  SOURCE FILE: Panel.h
--
--  PROGRAM:
--
--
--  FUNCTIONS:
--
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  NOTES:
--
----------------------------------------------------------------------------*/

#include <QtGui/qgraphicsview.h>
#include <string>
#include "../Comm/Commclient.h"

QT_BEGIN_NAMESPACE
class QTimeLine;
class Ui_BackSide;
QT_END_NAMESPACE

class RoundRectItem;

class Panel : public QGraphicsView
{
Q_OBJECT

private:
    QPointF posForLocation(int x, int y) const;

    QGraphicsScene *scene;
    RoundRectItem *selectionItem;
    RoundRectItem *baseItem;
    RoundRectItem *settingBaseItem;
    RoundRectItem *backItem;
    QGraphicsWidget *splash;
    QTimeLine *selectionTimeLine;
    QTimeLine *flipTimeLine;
    int selectedX, selectedY;

    QGraphicsItem ***grid;

    QPointF startPos;
    QPointF endPos;
    qreal xrot, yrot;
    qreal xrot2, yrot2;

    int width;
    int height;
    bool flipped;
    bool flipLeft;

    Ui_BackSide *ui;
    QMessageBox mbox;
    std::string selectedShip;

public:
    Panel();
    ~Panel();
    void quit();

public slots:
	void b1Clicked(){selectedShip = "jvship";}
    void b2Clicked(){selectedShip = "lvship";}
    void b3Clicked(){selectedShip = "nwship";}
    void b4Clicked(){selectedShip = "shship";}
    void b5Clicked(){selectedShip = "spship";}
    void b6Clicked(){selectedShip = "teship";}
    void b7Clicked(){selectedShip = "wbship";}
    void b8Clicked(){selectedShip = "weship";}


protected:
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);

private Q_SLOTS:
    void updateSelectionStep(qreal val);
    void updateFlipStep(qreal val);
    void flip();
    void closeEvent(QCloseEvent * e);
    void serverConnect(int);
    void errorConnect();
    void nameInUse();
};
