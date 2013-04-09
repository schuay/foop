#ifndef WALLTRANSFORMER_H
#define WALLTRANSFORMER_H

#include "gametransformer.h"

class WallTransformer : public GameTransformer
{
public:
    void transform(Game *game);
};

#endif // WALLTRANSFORMER_H
