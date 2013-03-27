#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsRectItem>

class CellItem : public QGraphicsRectItem
{
public:
    CellItem(QGraphicsItem *parent = 0);

    /** Takes a position in board (cell) coordinates, and applies it as pixel
     *  coordinates with the current cell size. */
    void setBoardPosition(int x, int y);

    void setCellSize(int cellSize);

private:
    void layout();

private:
    int cellSize;
    int x, y;
};

#endif // GRIDITEM_H
