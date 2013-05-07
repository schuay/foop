#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <QQueue>

/**
 * @brief The Snake class
 * Provides all methods and attributes
 * that are needed for one snake during the game.
 * The snake has one head and an added body with
 * a changing length. The snake has also a priority,
 * a driving direction and a unique id for identifing.
 */
class Snake
{
    friend class StateMessage;
public:
    /* Priority of the snake during the game*/
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

    /* 4 Possible driving directions of the snake. The order is significant! */
    enum Direction {
        DIR_UP,
        DIR_LEFT,
        DIR_DOWN,
        DIR_RIGHT,
        DIR_COUNT
    };

    Snake(int id, const QPoint &head);

    QQueue<QPoint> getBody() const;
    void setBody(QQueue<QPoint> body);

    void setPriority(Priority priority);
    Priority getPriority() const;

    Direction getDirection() const;
    void setDirection(Direction direction);

    Direction getNextDirection() const;
    void setNextDirection(Direction nextDirection);

    int getPendingGrowth() const;
    void setPendingGrowth(int pendingGrowth);
    int getId() const;

    int getPoints() const;

private:
    Snake(int id); /**< For deserialization. */

private:
    const int id;
    Priority priority;
    Direction direction, nextDirection;
    QQueue<QPoint> body;
    int pendingGrowth;
};

#endif // SNAKE_H
