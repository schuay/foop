#include "movetransformer.h"

#include "game.h"

void MoveTransformer::transform(Game *game)
{
    QSharedPointer<Board> board = game->getBoard();
    foreach(const QSharedPointer<Snake> &snake, board->getSnakes()) {
        snake->move();
    }
}
