#include "collisiontransformer.h"

#include <QSet>
#include <QTime>

#include "game.h"
#include "QsLog.h"

struct PartialRemoval {
    QSharedPointer<Snake> snake;
    QPoint point;
};

void handleCollisionWithSelf(const QSharedPointer<Snake> &snake,
                             QList<QSharedPointer<Snake> > &toRemove)
{
    QList<QPoint> body = snake->getBody();
    QPoint head = body.last();
    body.pop_back();

    /* Check if a snake's head collides with itself. If it does,
     * that snake has lost and is removed from the board. */

    foreach(const QPoint & p, body) {
        if (p == head) {
            QLOG_DEBUG() << "Detected collision with self";

            toRemove.append(snake);

            /* TODO: Send game over message. */
        }
    }
}

void handleCollisionWithOtherHead(const QSharedPointer<Snake> &snake,
                                  const QSharedPointer<Snake> &otherSnake,
                                  QList<QSharedPointer<Snake> > &toRemove)
{
    QPoint head = snake->getBody().last();

    QList<QPoint> otherBody = otherSnake->getBody();
    QPoint otherHead = otherBody.last();
    otherBody.pop_back();

    /* If it collides with another snake's head, the snake with the
     * higher priority wins. If priorities are equal, each snake
     * has a 50% chance to win. */

    if (head == otherHead) {
        QLOG_DEBUG() << "Detected collision with other head";

        QSharedPointer<Snake> winner, loser;
        bool iWin = (qrand() % 2) == 0;

        Snake::Priority thisPriority = snake->getPriority();
        Snake::Priority thatPriority = otherSnake->getPriority();

        if (thisPriority > thatPriority || (thisPriority == thatPriority && iWin)) {
            winner = snake;
            loser = otherSnake;
        } else {
            winner = otherSnake;
            loser = snake;
        }

        winner->setPendingGrowth(winner->getPendingGrowth() + loser->getBody().size());
        toRemove.append(loser);

        /* TODO: Send game over message. */
    }
}

void handleCollisionWithOtherBody(const QSharedPointer<Snake> &snake,
                                  const QSharedPointer<Snake> &otherSnake,
                                  QList<PartialRemoval> &toPartialRemove)
{
    QPoint head = snake->getBody().last();

    QList<QPoint> otherBody = otherSnake->getBody();
    otherBody.pop_back();

    /* If it collides with another snake's body, the other snake is
     * *partially* eaten. */

    for (int i = 0; i < otherBody.size(); i++) {
        QPoint p = otherBody[i];

        if (p != head) {
            continue;
        }

        PartialRemoval partialRemoval;
        partialRemoval.snake = otherSnake;
        partialRemoval.point = p;

        int removedElements = i + 1;
        snake->setPendingGrowth(snake->getPendingGrowth() + removedElements);

        QLOG_DEBUG() << "Detected collision with other body; gained"
                     << removedElements << "elements";

        toPartialRemove.append(partialRemoval);

        /* TODO: Game over message. */
    }
}

CollisionTransformer::CollisionTransformer()
{
    qsrand(QTime::currentTime().msec());
}

void CollisionTransformer::transform(Game *game)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    /* We will need to remove snakes with random access (= not the current one),
     * so mutable iterators don't really help. Maintain a list of snakes to remove,
     * and remove them all after finishing collision handling. */

    QList<QSharedPointer<Snake> > toRemove;
    QList<PartialRemoval> toPartialRemove;

    QSharedPointer<Board> board = game->getBoard();
    foreach(const QSharedPointer<Snake> &snake, board->getSnakes()) {
        handleCollisionWithSelf(snake, toRemove);

        QPoint head = snake->getBody().last();
        foreach(const QSharedPointer<Snake> &otherSnake, board->getSnakes()) {
            /* Skip self. */

            if (otherSnake == snake) {
                continue;
            }

            handleCollisionWithOtherHead(snake, otherSnake, toRemove);
            handleCollisionWithOtherBody(snake, otherSnake, toPartialRemove);

            /* TODO: There is a special case in which both snakes can collide head on
             * without triggering head collision handling: at t1, s1:(1,0) and s2:(2,0).
             * At t2, s1:(2,0) and s2:(1,0). */
        }
    }

    foreach(const PartialRemoval & partialRemoval, toPartialRemove) {
        QList<QPoint> body = partialRemoval.snake->getBody();
        int indexOfCollision = body.indexOf(partialRemoval.point);

        QQueue<QPoint> newBody;
        for (int i = (indexOfCollision < 0) ? 0 : indexOfCollision; i < body.size(); i++) {
            newBody.append(body.at(i));
        }

        partialRemoval.snake->setBody(newBody);
        partialRemoval.snake->setPendingGrowth(0);
    }

    foreach(const QSharedPointer<Snake> &snake, toRemove) {
        board->removeSnake(snake);
    }
}
