#ifndef TRACK_H
#define TRACK_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>

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
    QPointF m_P1;
    QPointF m_P2;
    QPen    m_pen;

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QPointF m_mouse_to_origin_movement;
    bool m_first_move;

};

#endif // TRACK_H
