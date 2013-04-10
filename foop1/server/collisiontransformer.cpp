#include "collisiontransformer.h"

#include "game.h"

void CollisionTransformer::transform(Game *game)
{
    QSharedPointer<Board> board = game->getBoard();
    foreach(const QSharedPointer<Snake> &snake, board->getSnakes()) {
        /* Check if a snake's head collides with itself. If it does,
         * that snake has lost and is removed from the board. */

        /* If it collides with another snake's head, the snake with the
         * higher priority wins. If priorities are equal, each snake
         * has a 50% chance to win. */

        /* If it collides with another snake's body, the other snake is
         * *partially* eaten. */
    }
}
