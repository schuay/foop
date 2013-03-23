#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsRectItem>

class CellItem : public QGraphicsRectItem
{
public:
    CellItem(QGraphicsItem *parent = 0);
};

#endif // GRIDITEM_H
