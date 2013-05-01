#ifndef MOVETRANSFORMER_H
#define MOVETRANSFORMER_H

#include "gametransformer.h"

/**
 * Handles the move operation of the snakes
*/
class MoveTransformer : public GameTransformer
{
public:

    /**
     * Each snake will be moved one chunk forward
     * regarding it's direction
     *
     * In:
     *  Game: the current game
    */
    void transform(Game *game);
};

#endif // MOVETRANSFORMER_H
