#ifndef COLLISIONTRANSFORMER_H
#define COLLISIONTRANSFORMER_H

#include "gametransformer.h"
#include "snake.h"

#include <QSharedPointer>
#include <QList>

struct PartialRemoval {
    QSharedPointer<Snake> snake;
    QPoint point;
};

/**
 * Handles the different collisions which are possible
 * between the snakes
 *
*/
class CollisionTransformer : public GameTransformer
{
public:
    CollisionTransformer();

    /**
     * Gets the game as input, calls all different collision-handlers
     * and removes the snakes from the game if necessary.
     *
     * In:
     *  - Game: the current game
    */
    void transform(Game *game);

private:

    /**
     * Checks if a snake collides with itself, if it collides
     * a gameOver message will be triggered
     *
     * In:
     *  Snake: the snake which should be checked for selfcollision
     * Out:
     *  QList<QSharedPointer<Snake>>: if the snake should be removed it will
     *      be added to the removeList
    */
    void handleCollisionWithSelf(const QSharedPointer<Snake> &snake,
                                 QList<QSharedPointer<Snake> > &toRemove);

    /**
     * Checks if a snake's head collides with a head of another snake.
     * The snake with the less priority will be removed if there is a head collision,
     * if the priorities are equal they have a 50:50 chance to win.     *
     *
     * In:
     *  Snake: the current snake
     *  Snake: the other snake
     *  int boardWidth: the width of the game-board
     *  int boardHeight: the height of the game-board
     * Out:
     *  QList<QSharedPointer<Snake>>: if the snake should be removed it will
     *      be added to the removeList
    */
    bool handleCollisionWithOtherHead(const QSharedPointer<Snake> &snake,
                                      const QSharedPointer<Snake> &otherSnake,
                                      QList<QSharedPointer<Snake> > &toRemove,
                                      int boardWidth, int boardHeight);

    /**
     * Checks if a snake's head collides with the body of another snake. If it collides
     * the snake will grow and the other snake shrink.
     *
     * In:
     *  Snake: the current snake
     *  Snake: the other snake
     * Out:
     *  QList<PartialRemove>: the cells which should be removed from the snake
    */
    void handleCollisionWithOtherBody(const QSharedPointer<Snake> &snake,
                                      const QSharedPointer<Snake> &otherSnake,
                                      QList<PartialRemoval> &toPartialRemove);

private:
    Game *game;

};

#endif // COLLISIONTRANSFORMER_H
