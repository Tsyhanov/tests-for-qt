#ifndef TRACK_H
#define TRACK_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include "itemhandler.h"

class Track : public QGraphicsItem
{
    //Q_OBJECT
public:
    Track();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void setPos(const QPointF &p);
    virtual void setPos(qreal x, qreal y);

    //item state
    bool Pressed;
private:
    QColor  m_color;
    QPointF m_P1, m_old_P1;
    QPointF m_P2, m_old_P2;
    QPen    m_pen;

protected:

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverMoveEvent (QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QPointF m_mouse_to_origin_movement;
    bool m_first_move;
    bool m_hovered;
    bool m_mouse_grab_handler;
    int m_vector_index;
    ItemHandler m_item_handler;//rect for grab

};

#endif // TRACK_H
