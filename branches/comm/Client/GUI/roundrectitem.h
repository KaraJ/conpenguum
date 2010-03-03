/*----------------------------------------------------------------------------
--  SOURCE FILE: roundrectitem.h
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
#include <QtGui/qgraphicsitem.h>
#include <QtGui/qbrush.h>

QT_BEGIN_NAMESPACE
class QGraphicsProxyWidget;
QT_END_NAMESPACE

class RoundRectItem : public QObject, public QGraphicsRectItem
{
//Q_OBJECT
public:
    RoundRectItem(const QRectF &rect, const QBrush &brush, QWidget *embeddedWidget = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;

    void setPixmap(const QPixmap &pixmap);

    qreal opacity() const;
    void setOpacity(qreal opacity);

Q_SIGNALS:
    void activated();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void updateValue(qreal value);

private:
    QBrush brush;
    QPixmap pix;
    QTimeLine timeLine;
    qreal lastVal;
    qreal opa;

    QGraphicsProxyWidget *proxyWidget;
};
