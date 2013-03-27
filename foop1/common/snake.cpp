#include "snake.h"

Snake::Snake()
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

QVariant Snake::toVariant() const
{
    QVariantMap map;
    map.insert("priority", priority);
    map.insert("direction", direction);

    /* TODO: Body. */

    return map;
}
