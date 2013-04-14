#include <QTime>
#include <QMap>

#include "board.h"

#include "QsLog.h"

Board::Board(int width, int height) :
    width(width),
    height(height)
{
}

int Board::getWidth() const
{
    return width;
}

int Board::getHeight() const
{
    return height;
}

QSharedPointer<Snake> Board::addSnake(int id)
{
    QSharedPointer<Snake> snake(new Snake(id, getRandomPosition()));
    snake->setPriority(getLeastAssignedPriority());
    snakes.append(snake);
    return snake;
}

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

void Board::removeSnake(const QSharedPointer<Snake> &snake)
{
    snakes.removeAll(snake);
}

QList<QSharedPointer<Snake> > Board::getSnakes() const
{
    return snakes;
}
