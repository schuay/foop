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

QSharedPointer<Snake> Board::addSnake(int id)
{
    QSharedPointer<Snake> snake(new Snake(id));
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
