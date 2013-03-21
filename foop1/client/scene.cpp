#include "scene.h"

#include "griditem.h"

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    addItem(new GridItem());
}
