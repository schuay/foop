#include "game.h"

#include "movetransformer.h"
#include "prioritytransformer.h"
#include "QsLog.h"
#include "walltransformer.h"

#define TURN_INTERVAL_MS (300)

Game::Game(int width, int height)
{
    board = QSharedPointer<Board>(new Board(width, height));

    /* Transformers will be executed in insertion order. */

    gameTransformers.append(QSharedPointer<GameTransformer>(new MoveTransformer()));
    gameTransformers.append(QSharedPointer<GameTransformer>(new WallTransformer()));
    gameTransformers.append(QSharedPointer<GameTransformer>(new PriorityTransformer()));

    connect(&timer, SIGNAL(timeout()), this, SLOT(processNewTurn()));
    timer.start(TURN_INTERVAL_MS);
}

QSharedPointer<Board> Game::getBoard() const
{
    return board;
}

void Game::processNewTurn()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    foreach(const QSharedPointer<GameTransformer> &t, gameTransformers) {
        t->transform(this);
    }

    emit newTurn();
}
