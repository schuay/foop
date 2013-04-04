#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include <QSharedPointer>

#include "snake.h"

class Board
{
    friend class StateMessage;
public:
    Board(int width, int height);

    int getWidth() const;
    int getHeight() const;

    QSharedPointer<Snake> addSnake(int id);
    QList<QSharedPointer<Snake> > getSnakes() const;

private:
    const int width, height;
    QList<QSharedPointer<Snake> > snakes;
};

#endif // BOARD_H
