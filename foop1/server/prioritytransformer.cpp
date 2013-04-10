#include "prioritytransformer.h"

#include "board.h"
#include "game.h"
#include "snake.h"

#define TURNS_PER_PRIORITY (50)

PriorityTransformer::PriorityTransformer()
    : iterations(0)
{
}

void PriorityTransformer::transform(Game *game)
{
    if (++iterations != TURNS_PER_PRIORITY) {
        return;
    }

    QSharedPointer<Board> board = game->getBoard();
    foreach(const QSharedPointer<Snake> &snake, board->getSnakes()) {
        int priority = (snake->getPriority() + 1) % Snake::PRI_COUNT;
        snake->setPriority((Snake::Priority)priority);
    }

    iterations = 0;
}
