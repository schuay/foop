#define KEY_ID ("id")

#include "identifymessage.h"

/**
 * @brief IdentifyMessage::IdentifyMessage
 * creates a new identifing message with a specific id
 * @param id unique id of the snake > 0
 */
IdentifyMessage::IdentifyMessage(int id)
{
    this->id = id;
}

/**
 * @brief IdentifyMessage::IdentifyMessage
 * retrieves the information - the id - of this incoming message
 * @param variant incoming element of the message != NULL
 */
IdentifyMessage::IdentifyMessage(const QVariant &variant)
{
    QMap<QString, QVariant> mapVariant = variant.toMap();
    id = mapVariant.value(KEY_ID).toInt();
}

/**
 * @brief IdentifyMessage::toVariant
 * putting the information of this message into a
 * transferable qvariant element for the outgoing message
 * @return the transferable qvariant element
 */
QVariant IdentifyMessage::toVariant() const
{
    QVariantMap v;
    v.insert(KEY_TYPE, getType());
    v.insert(KEY_ID, getId());

    return v;
}

/**
 * @brief IdentifyMessage::getType
 * returns the specific type of this message
 * @return the defined type of this message
 */
int IdentifyMessage::getType() const
{
    return MSG_IDENTIFY;
}

/**
 * @brief IdentifyMessage::getId
 * getting the information - the id - of this message
 * @return the id included in this message
 */
int IdentifyMessage::getId() const
{
    return id;
}
