#include "board.h"

Board::Board(int width, int height) :
    width(width),
    height(height)
{
    /* TODO: Temp. */

    snakes.append(QSharedPointer<Snake>(new Snake(0)));
    snakes.append(QSharedPointer<Snake>(new Snake(1)));
    snakes.append(QSharedPointer<Snake>(new Snake(2)));
}

int Board::getWidth() const
{
    return width;
}

int Board::getHeight() const
{
    return height;
}

QList<QSharedPointer<Snake> > Board::getSnakes() const
{
    return snakes;
}
