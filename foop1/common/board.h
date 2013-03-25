#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include <QSharedPointer>

#include "serializable.h"
#include "snake.h"

class Board : public Serializable
{
public:
    Board(int width, int height);

    int getWidth() const;
    int getHeight() const;

    QVariant toVariant() const;

private:
    const int width, height;
    QList<QSharedPointer<Snake> > snakes;
};

#endif // BOARD_H
