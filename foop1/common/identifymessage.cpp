#define KEY_ID ("id")

#include "identifymessage.h"

IdentifyMessage::IdentifyMessage(int id)
{
    this->id = id;
}

IdentifyMessage::IdentifyMessage(const QVariant &variant)
{
    QMap<QString, QVariant> mapVariant = variant.toMap();
    id = mapVariant.value(KEY_ID).toInt();
}

QVariant IdentifyMessage::toVariant() const
{
    QVariantMap v;
    v.insert(KEY_TYPE, getType());
    v.insert(KEY_ID, getId());

    return v;
}

int IdentifyMessage::getType() const
{
    return MSG_IDENTIFY;
}

int IdentifyMessage::getId() const
{
    return id;
}
