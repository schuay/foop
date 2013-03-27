#include "board.h"

Board::Board(int width, int height) :
    width(width),
    height(height)
{
    /* TODO: Temp. */

    snakes.append(QSharedPointer<Snake>(new Snake()));
    snakes.append(QSharedPointer<Snake>(new Snake()));
    snakes.append(QSharedPointer<Snake>(new Snake()));
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
