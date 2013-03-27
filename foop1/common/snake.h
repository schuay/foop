#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <QQueue>

#include "serializable.h"

class Snake : public Serializable
{
public:
    enum Priority {
        PRI_LOWEST,
        PRI_0 = 0,
        PRI_1,
        PRI_2,
        PRI_3,
        PRI_4,
        PRI_HIGHEST = 4
    };

    enum Direction {
        DIR_UP,
        DIR_DOWN,
        DIR_LEFT,
        DIR_RIGHT
    };

    Snake();

    QQueue<QPoint> getBody() const;

    QVariant toVariant() const;

private:
    Priority priority;
    Direction direction;
    QQueue<QPoint> body;
};

#endif // SNAKE_H
