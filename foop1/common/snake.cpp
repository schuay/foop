#include "snake.h"

Snake::Snake(int id, const QPoint &head) :
    id(id), pendingGrowth(6)
{
    priority = PRI_HIGHEST;
    direction = DIR_RIGHT;

    body.enqueue(head);
}

Snake::Snake(int id) :
    id(id)
{
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

    /* Growth. */

    if (pendingGrowth > 0) {
        pendingGrowth--;
    } else {
        (void)body.dequeue();
    }
}
