#include "game.h"
#include "walltransformer.h"


void WallTransformer::transform(Game *game)
{
    QSharedPointer<Board> board = game->getBoard();
    foreach(const QSharedPointer<Snake> &snake, board->getSnakes()) {
        QQueue<QPoint> body = snake->getBody();
        QPoint head = body.last();

        if (head.y() < 0) {
            head.setY(board->getHeight() - 1);
        } else if (head.y() >= board->getHeight()) {
            head.setY(0);
        }

        if (head.x() < 0) {
            head.setX(board->getWidth() - 1);
        } else if (head.x() >= board->getWidth()) {
            head.setX(0);
        }

        if (head != body.last()) {
            body.pop_back();
            body.enqueue(head);
            snake->setBody(body);
        }
    }
}
