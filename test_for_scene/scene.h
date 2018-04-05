#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include "track.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = 0);
    int getGridSize() const {return this->gridSize;}
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
private:
    int gridSize;
    Track *testtrack;
};

#endif // SCENE_H
