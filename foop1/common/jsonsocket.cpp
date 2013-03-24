#include "jsonsocket.h"

#include "QsLog.h"

JsonSocket::JsonSocket(int socketDescriptor)
{
    tcpSocket.setSocketDescriptor(socketDescriptor);

    parser.reset(new QJson::Parser());
    serializer.reset(new QJson::Serializer());

    connect(&tcpSocket, SIGNAL(readChannelFinished()), this, SLOT(onReadChannelFinished()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

QVariant JsonSocket::read()
{
    if (readQueue.isEmpty()) {
        return QVariant();
    }

    return readQueue.dequeue();
}

void JsonSocket::write(const QVariant &data)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << data;

    bool ok;
    QByteArray bytes = serializer->serialize(data, &ok);

    if (!ok) {
        QLOG_ERROR() << serializer->errorMessage();
        return;
    }

    tcpSocket.write(bytes);
}

void JsonSocket::onReadyRead()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    parseBuffer.append(tcpSocket.readAll());

    bool ok;
    QVariant result = parser->parse(parseBuffer, &ok);

    if (!ok) {
        /* The QJson implementation does not seem to recover well from
         * errors, forcing us to use a new instance for each failed attempt.
         * Alternatively, we could count braces ourselves and only attempt to
         * parse once we have a complete JSON snippet. However, that would
         * also mean accounting for special cases such as escaped braces.
         */
        parser.reset(new QJson::Parser());
        return;
    }

    /* Parsed a JSON object successfully; clear the buffer and handle
     * the incoming data. */

    QLOG_INFO() << "Received JSON:" << result;
    parseBuffer.clear();

    readQueue.append(result);
    emit readyRead();
}

void JsonSocket::onReadChannelFinished()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    emit readChannelFinished();
}
