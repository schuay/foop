#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QSharedPointer>
#include <QTimer>
#include <QMap>

#include "board.h"
#include "gametransformer.h"
#include "clientconnection.h"

/**
 * The Game contains all information about the game
 *
*/
class Game : public QObject
{
    Q_OBJECT
public:
    Game(int width, int height);

    QSharedPointer<Board> getBoard() const;

    /**
     * registers a incomming connection to be able to
     * send a gameover message to a certain player
     *
     * In:
     *  ClientConnection: the client connection
    */
    void registerConnection(ClientConnection *clientConnection);

    /**
     * returns the client connection for the given snake
    */
    ClientConnection *getClientConnection(const QSharedPointer<Snake> &snake) const;

signals:
    /**
     * Emitted when a new turn has begun and all related processing
     * (movement, collision detection and handling) has finished.
     */
    void newTurn();

public slots:
    void onSnakeRemove();

private slots:
    void processNewTurn();

private:
    /**
     * The game board, which includes all active snakes.
     */
    QSharedPointer<Board> board;

    /**
     * Each tick of the timer signifies a game 'turn', which
     * triggers actions such as actor movement, collision detection,
     * and collision handling.
     */
    QTimer timer;

    /**
     * All game transformers are called in order at the end of each turn.
     */
    QList<QSharedPointer<GameTransformer> > gameTransformers;

    QMap<QSharedPointer<Snake>, ClientConnection *> connections;
};

#endif // GAME_H
