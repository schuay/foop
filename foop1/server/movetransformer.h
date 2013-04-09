#ifndef MOVETRANSFORMER_H
#define MOVETRANSFORMER_H

#include "gametransformer.h"

class MoveTransformer : public GameTransformer
{
public:
    void transform(Game *game);
};

#endif // MOVETRANSFORMER_H
