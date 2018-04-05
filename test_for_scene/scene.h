#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include "track.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT

//ATTR
public:
    // abscissa grid step size
    static const int xGrid;
    // ordinate grid step size
    static const int yGrid;

public:
    explicit Scene(QWidget *parent = 0);
    static QPointF snapToGrid(const QPointF &p);
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
private:
    Track *testtrack;
};

#endif // SCENE_H
