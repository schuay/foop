#include "board.h"

Board::Board(int width, int height) :
    width(width),
    height(height)
{
}

int Board::getWidth() const
{
    return width;
}

int Board::getHeight() const
{
    return height;
}

QSharedPointer<Snake> Board::addSnake(int id)
{
    /* TODO: Figure out an unused cell to place the new snake. */

    QSharedPointer<Snake> snake(new Snake(id, QPoint(0, 0)));
    snakes.append(snake);
    return snake;
}

void Board::removeSnake(const QSharedPointer<Snake> &snake)
{
    snakes.removeAll(snake);
}

QList<QSharedPointer<Snake> > Board::getSnakes() const
{
    return snakes;
}
