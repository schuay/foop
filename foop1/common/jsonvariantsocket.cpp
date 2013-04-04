#include "jsonvariantsocket.h"

#include "QsLog.h"

JsonVariantSocket::JsonVariantSocket(QSharedPointer<QTcpSocket> tcpSocket, QObject *parent) :
    AbstractVariantSocket(parent),
    tcpSocket(tcpSocket)
{
    parser.reset(new QJson::Parser());
    serializer.reset(new QJson::Serializer());

    connect(tcpSocket.data(), SIGNAL(readChannelFinished()), this, SLOT(onReadChannelFinished()));
    connect(tcpSocket.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

QVariant JsonVariantSocket::read()
{
    if (readQueue.isEmpty()) {
        return QVariant();
    }

    return readQueue.dequeue();
}

void JsonVariantSocket::write(const QVariant &data)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << data;

    QByteArray bytes = serializer->serialize(data);

    tcpSocket->write(bytes);
}

void JsonVariantSocket::onReadyRead()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    parseBuffer.append(tcpSocket->readAll());

    if (!isJsonOk(parseBuffer)) {
        return;
    }

    bool ok;
    QVariant result = parser->parse(parseBuffer, &ok);

    if (!ok) {
        return;
    }

    /* Parsed a JSON object successfully; clear the buffer and handle
     * the incoming data. */

    QLOG_TRACE() << "Received JSON:" << result;
    parseBuffer.clear();

    readQueue.append(result);
    emit readyRead();
}

void JsonVariantSocket::onReadChannelFinished()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    emit readChannelFinished();
}

bool JsonVariantSocket::isJsonOk(const QByteArray &qbyteArray) const
{

    if (qbyteArray.length() < 2) {
        return false;
    }

    int squareBracketOpen = 0;
    int curlyBracketOpen = 0;

    for (int i = 0; i < qbyteArray.length(); i++) {
        switch (qbyteArray.at(i)) {
        case '{':
            curlyBracketOpen++;
            break;
        case '}':
            curlyBracketOpen--;
            break;
        case '[':
            squareBracketOpen++;
            break;
        case ']':
            squareBracketOpen--;
            break;
        }
    }

    return curlyBracketOpen == 0 && squareBracketOpen == 0;
}
