#ifndef DIRECTIONMESSAGE_H
#define DIRECTIONMESSAGE_H

#include "snake.h"
#include "message.h"

class DirectionMessage : public Message
{
public:
    DirectionMessage(Snake::Direction);
    DirectionMessage(const QVariant &variant);

    int getType() const;
    QVariant toVariant() const;

private:
    Snake::Direction direction;
};

#endif // DIRECTIONMESSAGE_H