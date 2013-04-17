#include "collisiontransformer.h"

#include <QSet>
#include <QTime>

#include "game.h"
#include "QsLog.h"

struct PartialRemoval {
    QSharedPointer<Snake> snake;
    int collisionIndex;
};

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

        foreach(const QSharedPointer<Snake> &otherSnake, board->getSnakes()) {
            /* Skip self. */

            if (otherSnake == snake) {
                continue;
            }

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

                continue;
            }

            /* If it collides with another snake's body, the other snake is
             * *partially* eaten. */

            for (int i = 0; i < otherBody.size(); i++) {
                QPoint p = otherBody[i];

                if (p != head) {
                    continue;
                }

                QLOG_DEBUG() << "Detected collision with other body";

                PartialRemoval partialRemoval;
                partialRemoval.snake = otherSnake;
                partialRemoval.collisionIndex = i + 1; /* Plus one because we've removed head. */

                int removedElements = otherBody.size() - i;
                snake->setPendingGrowth(snake->getPendingGrowth() + removedElements);

                toPartialRemove.append(partialRemoval);

                /* TODO: Game over message. */
            }
        }
    }

    foreach(const PartialRemoval & partialRemoval, toPartialRemove) {
        QList<QPoint> body = partialRemoval.snake->getBody().mid(partialRemoval.collisionIndex);
        QQueue<QPoint> newBody;
        foreach(const QPoint & p, body) {
            newBody.append(p);
        }
        partialRemoval.snake->setBody(newBody);
        partialRemoval.snake->setPendingGrowth(0);
    }

    foreach(const QSharedPointer<Snake> &snake, toRemove) {
        board->removeSnake(snake);
    }
}
