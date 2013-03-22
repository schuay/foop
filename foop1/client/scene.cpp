#include "scene.h"

#include "griditem.h"
#include "QsLog.h"
#include "QKeyEvent"

#define STEP_SIZE (10)

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    gridItem.reset(new GridItem());
    addItem(gridItem.data());
}

void Scene::onDirectionPress(int dx, int dy)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << dx << dy;

    gridItem->setX(gridItem->x() + dx * STEP_SIZE);
    gridItem->setY(gridItem->y() + dy * STEP_SIZE);
}

void Scene::keyPressEvent(QKeyEvent *keyEvent)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << keyEvent->key();

    switch (keyEvent->key()) {
    case Qt::Key_Left:
        onDirectionPress(-1, 0);
        break;
    case Qt::Key_Right:
        onDirectionPress(1, 0);
        break;
    case Qt::Key_Up:
        onDirectionPress(0, -1);
        break;
    case Qt::Key_Down:
        onDirectionPress(0, 1);
        break;
    default:
        break;
    }
}
