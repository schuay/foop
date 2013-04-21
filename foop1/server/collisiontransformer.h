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

class CollisionTransformer : public GameTransformer
{
public:
    CollisionTransformer();

    void transform(Game *game);

private:

    void handleCollisionWithSelf(const QSharedPointer<Snake> &snake,
                                 QList<QSharedPointer<Snake> > &toRemove);

    bool handleCollisionWithOtherHead(const QSharedPointer<Snake> &snake,
                                      const QSharedPointer<Snake> &otherSnake,
                                      QList<QSharedPointer<Snake> > &toRemove,
                                      int boardWidth, int boardHeight);

    void handleCollisionWithOtherBody(const QSharedPointer<Snake> &snake,
                                      const QSharedPointer<Snake> &otherSnake,
                                      QList<PartialRemoval> &toPartialRemove);

private:
    Game *game;

};

#endif // COLLISIONTRANSFORMER_H
