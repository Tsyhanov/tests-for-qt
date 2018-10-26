#include "track.h"
#include "scene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>

Track::Track():
    m_item_handler(10)
{
    Pressed = false;
    m_first_move = true;
    m_mouse_grab_handler = false;

    m_color = Qt::black;
    setFlags(QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);

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

    //draw handler
    if (isSelected()){
        m_item_handler.drawItemHandler(painter, QVector<QPointF>{m_P1, m_P2});
    }
}

void Track::setPos(const QPointF &p)
{
    QPointF pp = Scene::snapToGrid(p);
    QGraphicsItem::setPos(pp);
}

void Track::setPos(qreal x, qreal y) {
    setPos(QPointF(x, y));
}

void Track::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug("Track::hoverEnterEvent");
    m_hovered = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void Track::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isSelected()) return;

    QVector <QPointF> vector;
    vector << m_P1 << m_P2;

    int handler = m_item_handler.pointIsHoverHandler(event->pos(), vector);
    if (handler >= 0){
        setCursor(Qt::SizeAllCursor);
        //qDebug("Попали на хендлер для ресайза");
    }
    else
        setCursor(Qt::OpenHandCursor);
}

void Track::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug("Track::hoverLeaveEvent");
    m_hovered = false;
    unsetCursor();
    QGraphicsItem::hoverLeaveEvent(event);
}


void Track::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isSelected()){
        QVector <QPointF> vector;
        vector << m_P1 << m_P2;
        m_vector_index = m_item_handler.pointIsHoverHandler(event->pos(), vector);
        if (m_vector_index != -1)
            {
            //User click on an handler
                m_mouse_grab_handler = true;
                m_old_P1 = m_P1;
                m_old_P2 = m_P2;
                return;
             }
//    Pressed = true;
    }
    QGraphicsItem::mousePressEvent(event);
}

void Track::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    Pressed = false;
    m_mouse_grab_handler = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

void Track::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_mouse_grab_handler) {
        QPointF new_pos = event->pos();
        new_pos = mapFromScene(Scene::snapToGrid(event->scenePos()));
        prepareGeometryChange();
        m_vector_index == 0 ? m_P1 = new_pos : m_P2 = new_pos;
        qDebug("Track::mouseMoveEvent m_mouse_grab_handler");
        return;
    }

        QPointF old_pos = pos();
    //    qDebug() << "pos()" << pos();
        if (m_first_move){
            m_mouse_to_origin_movement = old_pos - event->buttonDownScenePos(Qt::LeftButton);
    //        qDebug() << "first move m_mouse_to_origin_movement" << m_mouse_to_origin_movement;
        }
    //    qDebug() << "scene pos()" << event->scenePos();
        QPointF expected_pos = event->scenePos() + m_mouse_to_origin_movement;
    //    qDebug() << "expected_pos" << expected_pos;
        setPos(expected_pos);

        if (m_first_move) m_first_move = false;

}
