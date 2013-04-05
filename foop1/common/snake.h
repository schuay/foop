#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <QQueue>

class Snake
{
    friend class StateMessage;
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

    Snake(int id);

    QQueue<QPoint> getBody() const;
    Priority getPriority() const;

    Direction getDirection() const;
    void setDirection(Direction direction);

private:
    const int id;
    Priority priority;
    Direction direction;
    QQueue<QPoint> body;
};

#endif // SNAKE_H
