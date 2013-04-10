#ifndef COLLISIONTRANSFORMER_H
#define COLLISIONTRANSFORMER_H

#include "gametransformer.h"

class CollisionTransformer : public GameTransformer
{
public:
    void transform(Game *game);
};

#endif // COLLISIONTRANSFORMER_H
