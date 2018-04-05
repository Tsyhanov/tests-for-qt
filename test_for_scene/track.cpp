#include "track.h"
#include <QDebug>

Track::Track()
{
    Pressed = false;
    m_color = Qt::black;
    setFlags(QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);

    m_pen.setWidth(8);
    m_pen.setBrush(Qt::black);

    m_P1.setX(10);
    m_P1.setY(10);
    m_P2.setX(40);
    m_P2.setY(10);
    qDebug("Track constructor");
}

QRectF Track::boundingRect() const
{
    return QRectF(0,0,50,50);
}


void Track::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(m_pen);
    painter->drawLine(m_P1, m_P2);
//  painter->drawRect(10, 10, 40, 10);
//  painter->fillRect(boundingRect(), color);

}


void Track::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Track::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

void Track::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}
