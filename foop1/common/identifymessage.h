#ifndef IDENTIFYMESSAGE_H
#define IDENTIFYMESSAGE_H

#include "message.h"

/**
 * @brief The IdentifyMessage class is sent to the client immediately after connecting.
 * This way the client knows which snake id represents the client's snake.
 */
class IdentifyMessage : public Message
{
public:
    IdentifyMessage(int);
    IdentifyMessage(const QVariant &variant);

    int getType() const;
    int getId() const;

    QVariant toVariant() const;

private:
    int id;
};

#endif // IDENTIFYMESSAGE_H
