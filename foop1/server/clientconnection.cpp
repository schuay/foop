#include "clientconnection.h"

#include "jsonvariantsocket.h"
#include "QsLog.h"
#include "statemessage.h"
#include "messagefactory.h"

ClientConnection::ClientConnection(int socketDescriptor, QSharedPointer<Board> board, QObject *parent) :
    QObject(parent),
    socketDescriptor(socketDescriptor),
    board(board)
{
}

void ClientConnection::run()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    QSharedPointer<QTcpSocket> tcpSocket(new QTcpSocket(this));
    tcpSocket->setSocketDescriptor(socketDescriptor);

    variantSocket.reset(new JsonVariantSocket(tcpSocket));

    connect(variantSocket.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(variantSocket.data(), SIGNAL(readChannelFinished()), this, SIGNAL(finished()));
}

void ClientConnection::newTurn()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    StateMessage stateMessage(board);
    variantSocket->write(stateMessage.toVariant());
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
    /*TODO: check type of received message and act accordingly */


    QLOG_INFO() << "Doing complicated things with received variant:" << data;
}
