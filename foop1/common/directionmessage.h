#ifndef DIRECTIONMESSAGE_H
#define DIRECTIONMESSAGE_H

#include "snake.h"
#include "message.h"

/**
 * @brief The DirectionMessage class
 * provides controls for transfering messages
 * of the snakes directions between server and client
 */
class DirectionMessage : public Message
{
public:
    DirectionMessage(Snake::Direction);
    DirectionMessage(const QVariant &variant);

    int getType() const;
    Snake::Direction getDirection() const;

    QVariant toVariant() const;

private:
    Snake::Direction direction;
};

#endif // DIRECTIONMESSAGE_H
