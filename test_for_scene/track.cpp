#include "track.h"
#include "scene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

Track::Track()
{
    Pressed = false;
    m_first_move = true;
    m_color = Qt::black;
    setFlags(QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);

    m_pen.setWidth(10);
    m_pen.setBrush(Qt::black);

    m_P1.setX(4);
    m_P1.setY(4);
    m_P2.setX(40);
    m_P2.setY(4);
    qDebug("Track constructor");
}

QRectF Track::boundingRect() const
{
    qreal p1_x = m_P1.x()-m_pen.width()/2;
    qreal p1_y = m_P1.y()-m_pen.width()/2;
    qreal p2_x = m_P2.x()+m_pen.width()/2;
    qreal p2_y = m_P2.y()+m_pen.width()/2;

    return QRectF(p1_x, p1_y, p2_x, p2_y);
}


void Track::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    painter->drawLine(m_P1, m_P2);
//  painter->drawRect(10, 10, 40, 10);
//  painter->fillRect(boundingRect(), color);
}


void Track::setPos(const QPointF &p)
{
    QPointF pp = Scene::snapToGrid(p);
    QGraphicsItem::setPos(pp);
}

void Track::setPos(qreal x, qreal y) {
    setPos(QPointF(x, y));
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
    QPointF old_pos = pos();
    qDebug() << "pos()" << pos();
    if (m_first_move){
        m_mouse_to_origin_movement = old_pos - event->buttonDownScenePos(Qt::LeftButton);
        qDebug() << "first move m_mouse_to_origin_movement" << m_mouse_to_origin_movement;
    }
    qDebug() << "scene pos()" << event->scenePos();
    QPointF expected_pos = event->scenePos() + m_mouse_to_origin_movement;
    qDebug() << "expected_pos" << expected_pos;

    setPos(expected_pos);

    if (m_first_move) m_first_move = false;
}
