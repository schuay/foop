#include "scene.h"

#include "QsLog.h"
#include "QKeyEvent"

#define STEP_SIZE (10)

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
}

void Scene::onDirectionPress(int dx, int dy)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << dx << dy;
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
