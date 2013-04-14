#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include <QSharedPointer>

#include "snake.h"

class Board;
typedef QSharedPointer<Board> BoardPtr;

class Board
{
    friend class StateMessage;
public:
    Board(int width, int height);

    int getWidth() const;
    int getHeight() const;

    QSharedPointer<Snake> addSnake(int id);
    void removeSnake(const QSharedPointer<Snake> &snake);
    QList<QSharedPointer<Snake> > getSnakes() const;

private:
    QPoint getRandomPosition();
    Snake::Priority getLeastAssignedPriority();


private:
    const int width, height;
    QList<QSharedPointer<Snake> > snakes;
};

#endif // BOARD_H
