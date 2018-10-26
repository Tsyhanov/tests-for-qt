#ifndef ITEMHANDLER_H
#define ITEMHANDLER_H
#include <QPainter>

class ItemHandler
{
public:
    ItemHandler(qreal size = 1);
    void drawItemHandler(QPainter *painter, const QPointF & point, bool color2 = false);
    void drawItemHandler(QPainter *painter, const QVector<QPointF> &points, bool color2 = false);

    bool pointIsInHandler (const QPointF &point, const QPointF &key_point) const;
    int pointIsHoverHandler (const QPointF &point, const QVector<QPointF> &vector) const;
    QVector<QRectF> handlerRect (const QVector<QPointF> &vector) const;

private:
    QRectF getRect (const QPointF &point) const;
    qreal m_size;
    qreal m_zoom_factor;

//ATTR
public:
    static QVector <QPointF> pointsForLine (const QLineF &line);
    static QLineF lineForPosAtIndex (const QLineF &old_line, const QPointF &pos, int index);
};

#endif // ITEMHANDLER_H
