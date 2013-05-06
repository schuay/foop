#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsRectItem>

/**
 * @brief The CellItem class
 * handles how many pixel are
 * between 2 cells
 */

class CellItem : public QGraphicsRectItem
{
public:
    CellItem(QGraphicsItem *parent = 0);

    /** Takes a position in board (cell) coordinates, and applies it as pixel
     *  coordinates with the current cell size.
     *  In: x x-Position on the board > 0
     *      y y-Position on the board > 0
     *
     */
    void setBoardPosition(int x, int y);

    /** Sets the Pixel-Size of a cell
     *  In: cellSize is the new Size of the cell
     */
    void setCellSize(int cellSize);

private:
    void layout();

private:
    int cellSize;
    int x, y;
};

#endif // GRIDITEM_H
