#include "snake.h"

Snake::Snake(int id) :
    id(id)
{
    /* TODO: Temp. */

    priority = PRI_HIGHEST;
    direction = DIR_UP;

    body.enqueue(QPoint(13, 17));
    body.enqueue(QPoint(13, 18));
    body.enqueue(QPoint(12, 18));
    body.enqueue(QPoint(11, 18));
}

QQueue<QPoint> Snake::getBody() const
{
    return body;
}

Snake::Priority Snake::getPriority() const
{
    return priority;
}

Snake::Direction Snake::getDirection() const
{
    return direction;
}

void Snake::setDirection(Direction direction)
{
    /* TODO: Validate the direction. At any time, only three
     * directions are valid (unless the snake consists only of its head). */
    this->direction = direction;
}

void Snake::move()
{
    /* TODO: We need to handle board edges somewhere.
     * In a collision transformer? */

    /* TODO: Movement transactions. */

    QPoint head = body.last();

    switch (direction) {
    case DIR_UP:
        head.setY(head.y() - 1);
        break;
    case DIR_DOWN:
        head.setY(head.y() + 1);
        break;
    case DIR_LEFT:
        head.setX(head.x() - 1);
        break;
    case DIR_RIGHT:
        head.setX(head.x() + 1);
        break;
    }

    body.enqueue(head);

    /* TODO: Growth. */

    (void)body.dequeue();
}
