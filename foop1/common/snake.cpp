#include "snake.h"

/**
 * @brief Snake::Snake
 * Creates a new snake with a unique id
 * and a beginning body size of 6.
 * @param id unique id > 0
 * @param head the head of the snake != NULL
 */
Snake::Snake(int id, const QPoint &head) :
    id(id), pendingGrowth(6)
{
    priority = PRI_HIGHEST;
    direction = DIR_RIGHT;
    nextDirection = DIR_RIGHT;

    body.enqueue(head);
}

/**
 * @brief Snake::Snake
 * creates a new snake with a unique id
 * @param id unique id > 0
 */
Snake::Snake(int id) :
    id(id)
{
}

/**
 * @brief Snake::getBody
 * returns the whole body of the snake
 * @return the body of the snake as a queue
 */
QQueue<QPoint> Snake::getBody() const
{
    return body;
}

/**
 * @brief Snake::setBody
 * sets the body of the snake
 * @param body != NULL
 */
void Snake::setBody(QQueue<QPoint> body)
{
    this->body = body;
}

/**
 * @brief Snake::setPriority
 * sets the specific new priority of the snake
 * @param priority != NULL and must be in the defined range
 */
void Snake::setPriority(Priority priority)
{
    this->priority = priority;
}

/**
 * @brief Snake::getPriority
 * getting the current priority of the snake
 * @return the current priority
 */
Snake::Priority Snake::getPriority() const
{
    return priority;
}

/**
 * @brief Snake::getDirection
 * getting the defined current driving direction of the snake
 * @return the defined current driving direction
 */
Snake::Direction Snake::getDirection() const
{
    return direction;
}

/**
 * @brief Snake::getId
 * getting the unique id of the snake
 * @return the unique id of the snake
 */
int Snake::getId() const
{
    return id;
}

/**
 * @brief Snake::setDirection
 * sets the new direction of the snake
 * @param direction != NULL and must be in the valid
 * defined range
 */
void Snake::setDirection(Direction direction)
{
    this->direction = direction;
}

/**
 * @brief Snake::getNextDirection
 * gets the next direction of the snake, that will
 * be the new driving direction on the next turn
 * @return the next driving direction
 */
Snake::Direction Snake::getNextDirection() const
{
    return nextDirection;
}

/**
 * @brief Snake::setNextDirection
 * sets the following driving direction of the snake,
 * also checks if this direction is valid ( a snake
 * cannot drive in its own body)
 * @param nextDirection != NULL and must be in the valid
 * defined range
 */
void Snake::setNextDirection(Direction nextDirection)
{
    /* Validate the direction. At any time, only three
     * directions are valid (unless the snake consists only of its head). */

    bool isReverse = ((nextDirection + 2) % DIR_COUNT) == direction;
    if (body.size() == 1 || !isReverse) {
        this->nextDirection = nextDirection;
    }
}

/**
 * @brief Snake::getPendingGrowth
 * get the current pendinggrowth of the body
 * of the snake
 * @return the current pendinggrowth
 */
int Snake::getPendingGrowth() const
{
    return pendingGrowth;
}

/**
 * @brief Snake::setPendingGrowth
 * sets the new pendinggrowth of the snake
 * @param pendingGrowth >= 0
 */
void Snake::setPendingGrowth(int pendingGrowth)
{
    this->pendingGrowth = pendingGrowth;
}

/**
 * @brief Snake::getPoints
 * getting the current points for the snake,
 * computed by the length and pendinggrowth of the snake
 * @return the current points for the snake
 */
int Snake::getPoints() const
{
    return getBody().length() + getPendingGrowth();
}
