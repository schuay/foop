#include "messagefactory.h"

#include "QsLog.h"
#include "statemessage.h"
#include "directionmessage.h"
#include "gameovermessage.h"

QSharedPointer<Message> MessageFactory::createMessage(const QVariant &variant)
{
    bool ok;
    int type = variant.toMap().value(KEY_TYPE).toInt(&ok);

    if (!ok) {
        QLOG_ERROR() << "The received variant does not have a type";
        return QSharedPointer<Message>();
    }

    switch (type) {
    case Message::MSG_STATE:
        return QSharedPointer<Message>(new StateMessage(variant));
    case Message::MSG_DIRECTION:
        return QSharedPointer<Message>(new DirectionMessage(variant));
    case Message::MSG_GAMEOVER:
        return QSharedPointer<Message>(new GameoverMessage(variant));
    default:
        QLOG_ERROR() << "The received variant has an unknown type:" << type;
        return QSharedPointer<Message>();
    }
}
