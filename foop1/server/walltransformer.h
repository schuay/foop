#ifndef WALLTRANSFORMER_H
#define WALLTRANSFORMER_H

#include "gametransformer.h"

/**
 * Handles the situation when a snake gets to
 * a boarder of the game
*/
class WallTransformer : public GameTransformer
{
public:

    /**
     * When the snakes next move would outside of the boarders of the game,
     * it will be set on the opposite of the boarder
     *
     * In:
     *  Game: the current game
    */
    void transform(Game *game);
};

#endif // WALLTRANSFORMER_H
