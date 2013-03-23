#include "game.h"

#include "QsLog.h"

#define TURN_INTERVAL_MS (500)

Game::Game(int width, int height)
{
    board = QSharedPointer<Board>(new Board(width, height));

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

    emit newTurn();
}
