#ifndef GAMEOVERMESSAGE_H
#define GAMEOVERMESSAGE_H

#include "message.h"

class GameoverMessage : public Message
{
public:
    GameoverMessage(int score, bool won);
    GameoverMessage(const QVariant &variant);

    int getType() const;
    QVariant toVariant() const;

private:
    int score;
    bool won;
};

#endif // GAMEOVERMESSAGE_H
