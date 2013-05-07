#ifndef JSONSOCKET_H
#define JSONSOCKET_H

#include <qjson/parser.h>
#include <qjson/serializer.h>
#include <QQueue>
#include <QSharedPointer>
#include <QScopedPointer>
#include <QTcpSocket>

#include "abstractvariantsocket.h"

/**
 * @brief The JsonVariantSocket class
 * this class provides the basic control elements,
 * e.g. reading/writing from/to the network,
 * for the information exchange between client and server,
 * here we used json for this network-traffic exchange
 */
class JsonVariantSocket : public AbstractVariantSocket
{
    Q_OBJECT
public:
    JsonVariantSocket(QSharedPointer<QTcpSocket> tcpSocket, QObject *parent = 0);

    QVariant read();
    void write(const QVariant &data);

    void close();

private slots:
    void onReadyRead();
    void onReadChannelFinished();

private:
    QScopedPointer<QJson::Parser> parser;
    QScopedPointer<QJson::Serializer> serializer;

    QByteArray parseBuffer;

    QSharedPointer<QTcpSocket> tcpSocket;

    QQueue<QVariant> readQueue;

};

#endif // JSONSOCKET_H
