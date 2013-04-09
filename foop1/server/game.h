#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QSharedPointer>
#include <QTimer>

#include "board.h"
#include "gametransformer.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game(int width, int height);

    QSharedPointer<Board> getBoard() const;

signals:
    /**
     * Emitted when a new turn has begun and all related processing
     * (movement, collision detection and handling) has finished.
     */
    void newTurn();

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
};

#endif // GAME_H
