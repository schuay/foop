#include "serverconnection.h"

#include <QTcpSocket>

#include "jsonvariantsocket.h"
#include "messagefactory.h"
#include "QsLog.h"
#include "directionmessage.h"

ServerConnection::ServerConnection(QString host, int port, QObject *parent) :
    QObject(parent),
    host(host),
    port(port)
{
}

void ServerConnection::run()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    QSharedPointer<QTcpSocket> tcpSocket(new QTcpSocket());
    tcpSocket->connectToHost(host, port);

    if (!tcpSocket->waitForConnected()) {
        QLOG_ERROR() << tcpSocket->errorString();
        emit finished();
    }

    variantSocket.reset(new JsonVariantSocket(tcpSocket));

    connect(variantSocket.data(), SIGNAL(readChannelFinished()), this, SIGNAL(finished()));
    connect(variantSocket.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void ServerConnection::onDirectionChange(Snake::Direction direction)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << direction;

    DirectionMessage directionMessage(direction);
    variantSocket->write(directionMessage.toVariant());
}

void ServerConnection::onReadyRead()
{
    QVariant v = variantSocket->read();

    if (v.isNull()) {
        return;
    }

    /* TODO: Deserialize the message and emit the appropriate signal. */

    QSharedPointer<Message> message = MessageFactory::createMessage(v);

    if (message.isNull()) {
        return;
    }
}
