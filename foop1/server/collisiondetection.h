#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "board.h"

class CollisionDetection
{
public:
    virtual void collides(QSharedPointer<Board> board);
};

#endif // COLLISIONDETECTION_H
