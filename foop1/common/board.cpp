#include <QTime>

#include "board.h"

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

    QSharedPointer<Snake> snake(new Snake(id, QPoint(randomX, randomY)));
    snakes.append(snake);
    return snake;
}

void Board::removeSnake(const QSharedPointer<Snake> &snake)
{
    snakes.removeAll(snake);
}

QList<QSharedPointer<Snake> > Board::getSnakes() const
{
    return snakes;
}
