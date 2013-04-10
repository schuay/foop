#ifndef PRIORITYTRANSFORMER_H
#define PRIORITYTRANSFORMER_H

#include "gametransformer.h"

class PriorityTransformer : public GameTransformer
{
public:
    PriorityTransformer();
    void transform(Game *game);

private:
    int iterations;
};

#endif // PRIORITYTRANSFORMER_H
