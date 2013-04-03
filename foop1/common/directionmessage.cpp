#define KEY_DIRECTION ("direction")

#include "directionmessage.h"

DirectionMessage::DirectionMessage(Snake::Direction direction):
    direction(direction)
{
}

DirectionMessage::DirectionMessage(const QVariant &variant)
{
    QMap<QString, QVariant> mapVariant = variant.toMap();
    direction = (Snake::Direction)mapVariant.value(KEY_DIRECTION).toInt();
}

QVariant DirectionMessage::toVariant() const
{
    QVariantMap v;
    v.insert(KEY_TYPE, getType());
    v.insert(KEY_DIRECTION, direction);

    return v;
}

int DirectionMessage::getType() const
{
    return MSG_STATE;
}
