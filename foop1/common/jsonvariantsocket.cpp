#include "jsonvariantsocket.h"

#include "QsLog.h"

#define EOM ("#")

/**
 * @brief JsonVariantSocket::JsonVariantSocket
 * creates a new network socket for the information exchange
 * @param tcpSocket the network tcpsocket that is used
 * @param parent the parent object
 */
JsonVariantSocket::JsonVariantSocket(QSharedPointer<QTcpSocket> tcpSocket, QObject *parent) :
    AbstractVariantSocket(parent),
    tcpSocket(tcpSocket)
{
    parser.reset(new QJson::Parser());
    serializer.reset(new QJson::Serializer());

    connect(tcpSocket.data(), SIGNAL(readChannelFinished()), this, SLOT(onReadChannelFinished()));
    connect(tcpSocket.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

/**
 * @brief JsonVariantSocket::read
 * Reads from the network-connection
 * @return the readed element from the network,
 * NULL if nothing is there to read
 */
QVariant JsonVariantSocket::read()
{
    if (readQueue.isEmpty()) {
        return QVariant();
    }

    return readQueue.dequeue();
}

/**
 * @brief JsonVariantSocket::write
 * writes an element to the network-connection
 * @param data, the element that is written to
 * the network != NULL
 */
void JsonVariantSocket::write(const QVariant &data)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << data;

    QByteArray bytes = serializer->serialize(data);

    tcpSocket->write(bytes);
    tcpSocket->write(EOM);
}

/**
 * @brief JsonVariantSocket::close
 * closes the conneciton of this socket to
 * the specific host
 */
void JsonVariantSocket::close()
{
    if (tcpSocket->isValid()) {
        tcpSocket->disconnectFromHost();
    }
}

void JsonVariantSocket::onReadyRead()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    /* The parser implementation is really picky. It expects exactly one
     * well-formed JSON object; if it ever fails, it never recovers
     * correctly. Thus, we need to ensure that only correct objects are
     * ever delivered to it. We do this by inserting an 'end-of-message'
     * character after each message. Of course this assumes that no valid
     * message contains this character. */

    parseBuffer.append(tcpSocket->readAll());

    int eomIndex = parseBuffer.indexOf(EOM);
    if (eomIndex == -1) {
        return;
    }

    /* We've received a complete message. Attempt to parse the message
     * and remove it from the incoming data buffer. */

    QByteArray msgBuffer = parseBuffer.left(eomIndex);
    parseBuffer = parseBuffer.remove(0, eomIndex + 1);

    bool ok;
    QVariant result = parser->parse(msgBuffer, &ok);

    if (!ok) {
        QLOG_ERROR() << "Failed to parse incoming message:" << msgBuffer;
        parser.reset(new QJson::Parser());
        return;
    }

    /* Parsed a JSON object successfully; clear the buffer and handle
     * the incoming data. */

    QLOG_TRACE() << "Received JSON:" << result;

    readQueue.append(result);
    emit readyRead();
}

void JsonVariantSocket::onReadChannelFinished()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    emit readChannelFinished();
}
