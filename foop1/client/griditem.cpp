#include "griditem.h"

#include <QBrush>

GridItem::GridItem(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    setRect(0, 0, 32, 32);
    setBrush(QBrush(Qt::red));
}
