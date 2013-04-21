#include "game.h"

#include <QSharedPointer>

#include "collisiontransformer.h"
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
    gameTransformers.append(QSharedPointer<GameTransformer>(new CollisionTransformer()));
    gameTransformers.append(QSharedPointer<GameTransformer>(new PriorityTransformer()));

    connect(&timer, SIGNAL(timeout()), this, SLOT(processNewTurn()));
    timer.start(TURN_INTERVAL_MS);

    //connect(board, SIGNAL(onSnakeRemove()), this, SLOT(onSnakeRemove()));
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


void Game::registerConnection(QSharedPointer<ClientConnection> clientConnection)
{
    connections[clientConnection->getSnake()] = clientConnection;
}

QSharedPointer<ClientConnection> Game::getClientConnection(QSharedPointer<Snake> snake)
{
    return connections.value(snake);
}

void Game::onSnakeRemove()
{

    QLOG_DEBUG() << "unregister snake";

}
