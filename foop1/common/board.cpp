#include <QTime>
#include <QMap>

#include "board.h"
#include "QsLog.h"

/**
 * @brief Board::Board
 * creates and sets height and width of the board
 * over the superclass
 * @param width > 0
 * @param height > 0
 */
Board::Board(int width, int height) :
    width(width),
    height(height)
{
}

/**
 * @brief Board::getWidth
 * getting the width of the board
 * @return width of the board
 */
int Board::getWidth() const
{
    return width;
}

/**
 * @brief Board::getHeight
 * getting the height of the board
 * @return height of the board
 */
int Board::getHeight() const
{
    return height;
}

/**
 * @brief Board::addSnake
 * adds a snake with a specific id to the board
 * @param id unique id of the snake, > 0
 * @return the new added snake
 */
QSharedPointer<Snake> Board::addSnake(int id)
{
    QSharedPointer<Snake> snake(new Snake(id, getRandomPosition()));
    snake->setPriority(getLeastAssignedPriority());
    snakes.append(snake);
    return snake;
}

/**
 * @brief Board::getRandomPosition
 * searches for a random start position for a
 * new snake on a empty position on the board
 * @return the x/y-start-position of the new snake
 */
QPoint Board::getRandomPosition()
{
    int randomX, randomY;

    qsrand(QTime::currentTime().msec());

    while (true) {
        randomX = qrand() % getWidth();
        randomY = qrand() % getHeight();

        foreach(const QSharedPointer<Snake> &snake, this->getSnakes()) {
            QQueue<QPoint> body = snake->getBody();
            if (body.contains(QPoint(randomX, randomY))) {
                continue;
            }
        }
        break;
    }

    return QPoint(randomX, randomY);

}

/**
 * @brief Board::getLeastAssignedPriority
 * getting the least assigned priority of the snakes
 * @return the least defined priority of the snakes
 */
Snake::Priority Board::getLeastAssignedPriority()
{
    QMap<Snake::Priority, int> map;
    foreach(const QSharedPointer<Snake> &snake, this->getSnakes()) {
        int oldValue = map.value(snake->getPriority());
        map.insert(snake->getPriority(), ++oldValue);
    }

    int min = this->getSnakes().count();

    int minPrio = 0;

    for (int i = 0; i < Snake::PRI_COUNT; i++) {
        if (map.value((Snake::Priority)i) < min) {
            min = map.value((Snake::Priority)i);
            minPrio = i;
        }
    }

    return (Snake::Priority)minPrio;
}

/**
 * @brief Board::removeSnake
 * removes a specific snake from the board
 * @param snake the snake that will be removed, != NULL
 */
void Board::removeSnake(const QSharedPointer<Snake> &snake)
{
    snakes.removeAll(snake);
}

/**
 * @brief Board::getSnakes
 * returning all snakes on the board
 * @return a list of all snakes
 */
QList<QSharedPointer<Snake> > Board::getSnakes() const
{
    return snakes;
}
