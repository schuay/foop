#include "clientconnection.h"

#include "QsLog.h"

ClientConnection::ClientConnection(int socketDescriptor, QSharedPointer<Board> board, QObject *parent) :
    QObject(parent),
    socketDescriptor(socketDescriptor),
    board(board)
{
}

void ClientConnection::run()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    jsonSocket.reset(new JsonSocket(socketDescriptor));

    connect(jsonSocket.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(jsonSocket.data(), SIGNAL(readChannelFinished()), this, SIGNAL(finished()));
}

void ClientConnection::newTurn()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    jsonSocket->write(board->toVariant());
}

void ClientConnection::onReadyRead()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    QVariant data = jsonSocket->read();
    QLOG_INFO() << "Doing complicated things with received variant:" << data;
}
