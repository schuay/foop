#ifndef GAMEOVERMESSAGE_H
#define GAMEOVERMESSAGE_H

#include "message.h"

/**
 * @brief The GameoverMessage class
 * provides controls for transfering messages
 * of the game-status between server and client
 */
class GameoverMessage : public Message
{
public:
    GameoverMessage(int score, bool won);
    GameoverMessage(const QVariant &variant);

    int getType() const;
    bool getWon() const;

    QVariant toVariant() const;

private:
    int score;
    bool won;
};

#endif // GAMEOVERMESSAGE_H
