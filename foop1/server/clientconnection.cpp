#include "clientconnection.h"

#include "QsLog.h"

ClientConnection::ClientConnection(int socketDescriptor, QSharedPointer<Board> board, QObject *parent) :
    QObject(parent),
    socketDescriptor(socketDescriptor),
    board(board)
{
}

void ClientConnection::process()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    tcpSocket.reset(new QTcpSocket(this));
    if (!tcpSocket->setSocketDescriptor(socketDescriptor)) {
        QLOG_ERROR() << tcpSocket->error();
        emit finished();
        return;
    }

    connect(tcpSocket.data(), SIGNAL(readyRead()), this, SLOT(read()));
    connect(tcpSocket.data(), SIGNAL(readChannelFinished()), this, SIGNAL(finished()));

    parser.reset(new QJson::Parser());
    serializer.reset(new QJson::Serializer());
}

void ClientConnection::newTurn()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    QByteArray data = serializer->serialize(board->toVariant());
    tcpSocket->write(data);
}

void ClientConnection::read()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    buffer.append(tcpSocket->readAll().trimmed());

    bool ok;
    QVariant result = parser->parse(buffer, &ok);

    if (!ok) {
        /* The QJson implementation does not seem to recover well from
         * errors, forcing us to use a new instance for each failed attempt.
         * Alternatively, we could count braces ourselves and only attempt to
         * parse once we have a complete JSON snippet.
         */
        parser.reset(new QJson::Parser());
        return;
    }

    /* Parsed a JSON object successfully; clear the buffer and handle
     * the incoming data. */

    QLOG_INFO() << "Received JSON:" << result;
    buffer.clear();
}
