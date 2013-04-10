#include "cellitem.h"

#include <QBrush>
#include <QPen>

#include <stdio.h>

/** How many pixels between two cells. */
#define CELL_SEPARATOR (1)

CellItem::CellItem(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    setBrush(QBrush(Qt::lightGray));
    setPen(QPen(Qt::NoPen));
}

void CellItem::setBoardPosition(int x, int y)
{
    this->x = x;
    this->y = y;

    layout();
}

void CellItem::setCellSize(int cellSize)
{
    this->cellSize = cellSize;

    layout();
}

void CellItem::layout()
{
    //printf("Offset: %d %d\n", offset.x(), offset.y());
    setRect(0, 0, cellSize - CELL_SEPARATOR, cellSize - CELL_SEPARATOR);
    setPos(x * cellSize, y * cellSize);
}
