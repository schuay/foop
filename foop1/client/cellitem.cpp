#include "cellitem.h"

#include <QBrush>
#include <QPen>

CellItem::CellItem(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    setBrush(QBrush(Qt::lightGray));
    setPen(QPen(Qt::NoPen));
}
