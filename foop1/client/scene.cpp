#include "scene.h"

#include "griditem.h"
#include "QsLog.h"
#include "QKeyEvent"

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    addItem(new GridItem());
}

void Scene::keyPressEvent(QKeyEvent *keyEvent)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << keyEvent->key();

    switch (keyEvent->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        /* TODO: Handle these. */
        break;
    default:
        break;
    }
}
