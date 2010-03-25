/*----------------------------------------------------------------------------
--  SOURCE FILE: splashitem.h
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

#include <QtCore/qobject.h>
#include <QtCore/qtimeline.h>
#include <QtGui/qgraphicswidget.h>

class SplashItem : public QGraphicsWidget
{
	Q_OBJECT
public:
    SplashItem(QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void keyPressEvent(QKeyEvent *event);

private Q_SLOTS:
    void setValue(qreal value);

private:
    QTimeLine *timeLine;
    QString text;
    qreal opacity;
};
