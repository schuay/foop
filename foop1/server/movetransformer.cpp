#include "movetransformer.h"

#include "game.h"

void MoveTransformer::transform(Game *game)
{
    QSharedPointer<Board> board = game->getBoard();
    foreach(const QSharedPointer<Snake> &snake, board->getSnakes()) {
        snake->setDirection(snake->getNextDirection());

        QQueue<QPoint> body = snake->getBody();
        QPoint head = body.last();

        switch (snake->getDirection()) {
        case Snake::DIR_UP:
            head.ry()--;
            break;
        case Snake::DIR_DOWN:
            head.ry()++;
            break;
        case Snake::DIR_LEFT:
            head.rx()--;
            break;
        case Snake::DIR_RIGHT:
            head.rx()++;
            break;
        }

        body.enqueue(head);

        /* Growth. */

        int pendingGrowth = snake->getPendingGrowth();
        if (pendingGrowth > 0) {
            snake->setPendingGrowth(pendingGrowth - 1);
        } else {
            (void)body.dequeue();
        }

        snake->setBody(body);
    }
}
