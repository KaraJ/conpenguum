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

public:
    Panel();
    ~Panel();
    void quit();

protected:
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);

private Q_SLOTS:
    void updateSelectionStep(qreal val);
    void updateFlipStep(qreal val);
    void flip();
};
