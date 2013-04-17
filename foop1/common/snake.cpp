#include "snake.h"

Snake::Snake(int id, const QPoint &head) :
    id(id), pendingGrowth(6)
{
    priority = PRI_HIGHEST;
    direction = DIR_RIGHT;
    nextDirection = DIR_RIGHT;

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

void Snake::setPriority(Priority priority)
{
    this->priority = priority;
}

Snake::Priority Snake::getPriority() const
{
    return priority;
}

Snake::Direction Snake::getDirection() const
{
    return direction;
}

int Snake::getId() const
{
    return id;
}

void Snake::setDirection(Direction direction)
{
    this->direction = direction;
}

Snake::Direction Snake::getNextDirection() const
{
    return nextDirection;
}

void Snake::setNextDirection(Direction nextDirection)
{
    /* Validate the direction. At any time, only three
     * directions are valid (unless the snake consists only of its head). */

    bool isReverse = ((nextDirection + 2) % DIR_COUNT) == direction;
    if (body.size() == 1 || !isReverse) {
        this->nextDirection = nextDirection;
    }
}

int Snake::getPendingGrowth() const
{
    return pendingGrowth;
}

void Snake::setPendingGrowth(int pendingGrowth)
{
    this->pendingGrowth = pendingGrowth;
}

int Snake::getPoints() const
{
    return getBody().length() + getPendingGrowth();
}
