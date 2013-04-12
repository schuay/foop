#include "collisiontransformer.h"

#include <QSet>

#include "game.h"
#include "QsLog.h"

void CollisionTransformer::transform(Game *game)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    /* We will need to remove snakes with random access (= not the current one),
     * so mutable iterators don't really help. Maintain a list of snakes to remove,
     * and remove them all after finishing collision handling. */

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
                /* TODO: Delete snake, send game over message. */
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
                /* TODO: Increment winner's length, delete other snake, send game over message. */
            }

            /* If it collides with another snake's body, the other snake is
             * *partially* eaten. */

            foreach(const QPoint & p, otherBody) {
                if (p == head) {
                    QLOG_DEBUG() << "Detected collision with other body";
                    /* TODO: Cut off other's body, increment own length, delete other snake, game over message. */
                }
            }
        }
    }
}
