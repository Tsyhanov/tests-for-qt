#include "scene.h"
#include <QDebug>
#include <QPainter>

const int   Scene::xGrid  = 10;
const int   Scene::yGrid  = 10;

Scene::Scene(QWidget *parent)
{
    qDebug("scene constructor");
    testtrack = new Track();
    testtrack->setPos(30,30);
    addItem(testtrack);
}

QPointF Scene::snapToGrid(const QPointF &p)
{
    //Return a point snapped to the grid
    int p_x = qRound(p.x() / Scene::xGrid) * Scene::xGrid;
    int p_y = qRound(p.y() / Scene::yGrid) * Scene::yGrid;
    return (QPointF(p_x, p_y));
}

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    qreal limite_x = rect.x() + rect.width();
    qreal limite_y = rect.y() + rect.height();

    int g_x = (int)ceil(rect.x());
    while (g_x % xGrid) ++ g_x;
    int g_y = (int)ceil(rect.y());
    while (g_y % yGrid) ++ g_y;

    QPolygon points;
    for (int gx = g_x ; gx < limite_x ; gx += xGrid) {
        for (int gy = g_y ; gy < limite_y ; gy += yGrid) {
            points << QPoint(gx, gy);
        }
    }
    painter->drawPoints(points);
}


void Scene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug("Scene::dragMoveEvent");
}
