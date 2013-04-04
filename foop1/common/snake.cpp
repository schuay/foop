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
