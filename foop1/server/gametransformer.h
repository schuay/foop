#ifndef GAMETRANSFORMER_H
#define GAMETRANSFORMER_H

#include <QSharedPointer>

class Game;

class GameTransformer
{
public:
    virtual ~GameTransformer() { }
    virtual void transform(Game *game) = 0;
};

#endif // GAMETRANSFORMER_H
