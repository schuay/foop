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
        PRI_HIGHEST = 4,
        PRI_COUNT
    };

    enum Direction {
        DIR_UP,
        DIR_DOWN,
        DIR_LEFT,
        DIR_RIGHT
    };

    Snake(int id, const QPoint &head);

    QQueue<QPoint> getBody() const;
    void setBody(QQueue<QPoint> body);

    void setPriority(Priority priority);
    Priority getPriority() const;

    Direction getDirection() const;
    void setDirection(Direction direction);

    int getPendingGrowth() const;
    void setPendingGrowth(int pendingGrowth);
    int getId() const;

    int getPoints() const;

private:
    Snake(int id); /**< For deserialization. */

private:
    const int id;
    Priority priority;
    Direction direction;
    QQueue<QPoint> body;
    int pendingGrowth;
};

#endif // SNAKE_H
