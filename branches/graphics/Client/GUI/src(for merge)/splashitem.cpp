/*----------------------------------------------------------------------------
--  SOURCE FILE: splashitem.cpp
--
--  PROGRAM: SplashItem
--
--  FUNCTIONS:
--      SplashItem          (QGraphicsItem *parent = 0);
--      void paint          (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
--      void keyPressEvent  (QKeyEvent *event);
--      void setValue       (qreal value);
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  NOTES:
--      Sets up the namebox for the title.
----------------------------------------------------------------------------*/

#include "splashitem.h"
#include <QtGui/QtGui>

/*--------------------------------------------------------------------------------------
--  Function: SplashItem
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: SplashItem::SplashItem(QGraphicsItem *parent)
--      parent - the widget which this item belongs to
--
--  RETURNS: SplashItem - the new text box at the top of the screen.
--
--  Notes:
--      The constructor for the splashitem displayed at the top of the screen.
--------------------------------------------------------------------------------------*/
SplashItem::SplashItem(QGraphicsItem *parent) : QGraphicsWidget(parent)
{
    opacity = 1.0;

    timeLine = new QTimeLine(350);
    timeLine->setCurveShape(QTimeLine::EaseInCurve);
    connect(timeLine, SIGNAL(valueChanged(qreal)), this, SLOT(setValue(qreal)));

    text = tr("CONPENGUUM");
    resize(400, 175);
}


/*--------------------------------------------------------------------------------------
--  Function: paint
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: void SplashItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
--      painter - the QPainter which is in charge of the colours and sizes of the object.
--      QStyleOptionGraphicsItem - default value
--      QWidget - default value.
--
--  RETURNS: void
--
--  Notes:
--      Paints the actual object onto the screen.
--------------------------------------------------------------------------------------*/
void SplashItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setOpacity(opacity);
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(QColor(250, 5, 20, 150));
    painter->setClipRect(rect());
    painter->drawRoundRect(3, -100 + 3, 400 - 6, 150 - 6);

    QRectF textRect = rect().adjusted(10, 10, -10, -10);
    int flags = Qt::AlignTop | Qt::AlignHCenter | Qt::TextWordWrap;

    QFont font;
    font.setPixelSize(18);
    painter->setPen(Qt::black);
    painter->setFont(font);
    painter->drawText(textRect, flags, text);
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
--  INTERFACE: void SplashItem::keyPressEvent(QKeyEvent *)
--      QKeyEvent - default value.
--
--  RETURNS: void
--
--  Notes:
--      Handles any keyboard event that happens.
--------------------------------------------------------------------------------------*/
void SplashItem::keyPressEvent(QKeyEvent * /* event */)
{
    if (timeLine->state() == QTimeLine::NotRunning)
        timeLine->start();
}


/*--------------------------------------------------------------------------------------
--  Function: setValue
--
--  DATE: Feb 1, 2010
--
--  DESIGNER: Nokia
--
--  PROGRAMMER REVISIONS: Daraius Dastoor
--
--  INTERFACE: void SplashItem::setValue(qreal value)
--      value - either 1 or 0, if the key is going up or down.
--
--  RETURNS: void
--
--  Notes:
--      When the key is pressed, move the box off the screen, make it transparent, and
--      hide it.
--------------------------------------------------------------------------------------*/
void SplashItem::setValue(qreal value)
{
    opacity = 1 - value;
    setPos(x(), scene()->sceneRect().top() - rect().height() * value);
    if (value == 1)
        hide();
}
