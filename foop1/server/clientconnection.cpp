#include "clientconnection.h"

#include "jsonvariantsocket.h"
#include "QsLog.h"
#include "directionmessage.h"
#include "statemessage.h"
#include "messagefactory.h"
#include "identifymessage.h"
#include "gameovermessage.h"

ClientConnection::ClientConnection(int socketDescriptor, QSharedPointer<Board> board, QObject *parent) :
    QObject(parent),
    socketDescriptor(socketDescriptor),
    board(board)
{
    snake = QSharedPointer<Snake>(board->addSnake(socketDescriptor));
}

void ClientConnection::run()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    QSharedPointer<QTcpSocket> tcpSocket(new QTcpSocket(this));
    tcpSocket->setSocketDescriptor(socketDescriptor);

    variantSocket.reset(new JsonVariantSocket(tcpSocket));

    // tell the client which snake belongs to him/her
    IdentifyMessage identifyMessage(snake->getId());
    variantSocket->write(identifyMessage.toVariant());

    connect(variantSocket.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(variantSocket.data(), SIGNAL(readChannelFinished()), this, SLOT(onReadChannelFinished()));
}

void ClientConnection::newTurn()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    StateMessage stateMessage(board, socketDescriptor);
    variantSocket->write(stateMessage.toVariant());
}

void ClientConnection::gameOver()
{
    GameoverMessage gameOverMessage(0, false);
    variantSocket->write(gameOverMessage.toVariant());
}

void ClientConnection::onReadyRead()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    QVariant data = variantSocket->read();
    QSharedPointer<Message> message = MessageFactory::createMessage(data);

    if (message.isNull()) {
        QLOG_ERROR() << "The received message cannot be created." << data;
        return;
    }

    if (message->getType() != Message::MSG_DIRECTION) {
        QLOG_ERROR() << "The received message has an invalid type:" << message->getType();
        return;
    }

    QSharedPointer<DirectionMessage> dirMessage = qSharedPointerCast<DirectionMessage>(message);
    snake->setNextDirection(dirMessage->getDirection());
}

void ClientConnection::onReadChannelFinished()
{
    QLOG_DEBUG() << __PRETTY_FUNCTION__;

    board->removeSnake(snake);
    emit finished();
}

QSharedPointer<Snake> ClientConnection::getSnake()
{
    return snake;
}
