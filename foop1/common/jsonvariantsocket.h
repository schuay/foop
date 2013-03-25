#ifndef JSONSOCKET_H
#define JSONSOCKET_H

#include <qjson/parser.h>
#include <qjson/serializer.h>
#include <QQueue>
#include <QSharedPointer>
#include <QScopedPointer>
#include <QTcpSocket>

#include "abstractvariantsocket.h"

class JsonVariantSocket : public AbstractVariantSocket
{
    Q_OBJECT
public:
    JsonVariantSocket(QSharedPointer<QTcpSocket> tcpSocket, QObject *parent = 0);

    QVariant read();
    void write(const QVariant &data);

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
