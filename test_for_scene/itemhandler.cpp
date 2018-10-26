#include "itemhandler.h"
#include <QPainter>
#include <QDebug>

ItemHandler::ItemHandler(qreal size):
    m_size(size),
    m_zoom_factor(1)
{
}

void ItemHandler::drawItemHandler(QPainter *painter, const QPointF &point, bool color2)
{
    QColor inner(0xFF, 0xFF, 0xFF);
    QColor outer(0x00, 0x61, 0xFF);

    m_zoom_factor = 1.0/painter->transform().m11();

    painter->save();
    painter->setBrush(QBrush(inner));
    QPen square_pen(QBrush(outer), 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    square_pen.setCosmetic(true);
    painter->setPen(square_pen);
    painter->drawRect(getRect(point));
    painter->restore();
}


void ItemHandler::drawItemHandler(QPainter *painter, const QVector<QPointF> &points, bool color2) {
    foreach(QPointF point, points)
        drawItemHandler(painter, point, color2);
}


/*
 * @param point : point to compare
 * @param key_point : point at the center of handler
 * (the point to modify, for exemple the corner of a rectangle)
 * @return true if point is in a handler. else false
 * определим относится ли точка к хендлеру
 */
bool ItemHandler::pointIsInHandler(const QPointF &point, const QPointF &key_point) const
{
    return (getRect(key_point).contains(point));
}

/*
 * @param point : point to compare
 * @param vector : vector of key_point
 * (the point to modify, for exemple the corners of a rectangle)
 * @return if point is hover an handler,
 *  return the index of the hovered key_point in the vector, else return -1
 * определим индекс хендлера(для линии - их всего 2, для квадрата 8)
 */
int ItemHandler::pointIsHoverHandler(const QPointF &point, const QVector<QPointF> &vector) const
{
    foreach (QPointF key_point, vector)
        if (pointIsInHandler(point, key_point))
            return vector.indexOf(key_point);

    return -1;
}

/*
 * Return the rect of the handler for all key_point in vector
 * (the point to modify, for exemple the corners of a rectangle)
 * The order of rect in the returned vector is the same as the given vector.
 * @param vector
 * @return
 */
QVector<QRectF> ItemHandler::handlerRect(const QVector<QPointF> &vector) const
{
    QVector <QRectF> rect_vector;

    foreach(QPointF point, vector)
        rect_vector << getRect(point);

    return rect_vector;
}


QRectF ItemHandler::getRect(const QPointF &point) const
{
    qreal rect_size = m_size * m_zoom_factor;
    QRectF rect(point.x() - rect_size/2, point.y() - rect_size/2, rect_size, rect_size);
    return rect;
}

//2 points from line
QVector<QPointF> ItemHandler::pointsForLine(const QLineF &line)
{
    return (QVector<QPointF> {line.p1(), line.p2()});
}

//по сути новая линия после того как тянули за хендлер с индексом index
QLineF ItemHandler::lineForPosAtIndex(const QLineF &old_line, const QPointF &pos, int index)
{
    QLineF line = old_line;
    index == 0 ? line.setP1(pos) : line.setP2(pos);
    return line;
}
