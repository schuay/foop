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

void Snake::setBody(QQueue<QPoint> body)
{
    this->body = body;
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

int Snake::getPendingGrowth() const
{
    return pendingGrowth;
}

void Snake::setPendingGrowth(int pendingGrowth)
{
    this->pendingGrowth = pendingGrowth;
}
