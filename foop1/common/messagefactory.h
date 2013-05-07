#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include <QSharedPointer>

#include "message.h"

/**
 * @brief The MessageFactory class
 * provides the factory for all defined messages that are
 * used in client/server-connection during the game
 */
class MessageFactory
{
public:
    static QSharedPointer<Message> createMessage(const QVariant &variant);

private:
    MessageFactory();
};

#endif // MESSAGEFACTORY_H
