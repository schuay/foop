#define KEY_DIRECTION ("direction")

#include "directionmessage.h"

/**
 * @brief DirectionMessage::DirectionMessage
 * creates a new direction message, with a specific
 * direction of the snake
 * @param direction a defined direction of the snake
 */
DirectionMessage::DirectionMessage(Snake::Direction direction):
    direction(direction)
{
}

/**
 * @brief DirectionMessage::DirectionMessage
 * getting the direction of an incoming message in a qvariant element
 * client
 * @param variant the packed message from the client != NULL
 */
DirectionMessage::DirectionMessage(const QVariant &variant)
{
    QMap<QString, QVariant> mapVariant = variant.toMap();
    direction = (Snake::Direction)mapVariant.value(KEY_DIRECTION).toInt();
}

/**
 * @brief DirectionMessage::toVariant
 * converts this message for transfering to the server
 * @return a qvariant element of this message for exchange
 * between client and server
 */
QVariant DirectionMessage::toVariant() const
{
    QVariantMap v;
    v.insert(KEY_TYPE, getType());
    v.insert(KEY_DIRECTION, direction);

    return v;
}

/**
 * @brief DirectionMessage::getType
 * returns the specific type of this message
 * @return the defined type of this message
 */
int DirectionMessage::getType() const
{
    return MSG_DIRECTION;
}

/**
 * @brief DirectionMessage::getDirection
 * returns the direction that is included in this message
 * @return the defined direction in this message
 */
Snake::Direction DirectionMessage::getDirection() const
{
    return direction;
}
