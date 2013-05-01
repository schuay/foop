#ifndef PRIORITYTRANSFORMER_H
#define PRIORITYTRANSFORMER_H

#include "gametransformer.h"

/**
 * Handles the different priorities for the snakes.
*/
class PriorityTransformer : public GameTransformer
{
public:
    PriorityTransformer();

    /**
     * After a certain amount of steps the priorities of the
     * snakes will be changed.
     *
     * In:
     *  Game: the current game
    */
    void transform(Game *game);

private:
    int iterations;
};

#endif // PRIORITYTRANSFORMER_H
