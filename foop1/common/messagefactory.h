#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include <QSharedPointer>

#include "message.h"

class MessageFactory
{
public:
    static QSharedPointer<Message> createMessage(const QVariant &variant);

private:
    MessageFactory();
};

#endif // MESSAGEFACTORY_H
