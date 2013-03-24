#ifndef JSONSOCKET_H
#define JSONSOCKET_H

#include <qjson/parser.h>
#include <qjson/serializer.h>
#include <QQueue>
#include <QScopedPointer>
#include <QTcpSocket>

#include "abstractvariantsocket.h"

class JsonVariantSocket : public AbstractVariantSocket
{
    Q_OBJECT
public:
    JsonVariantSocket(int socketDescriptor);

    QVariant read();
    void write(const QVariant &data);

private slots:
    void onReadyRead();
    void onReadChannelFinished();

private:
    QScopedPointer<QJson::Parser> parser;
    QScopedPointer<QJson::Serializer> serializer;

    QByteArray parseBuffer;

    QTcpSocket tcpSocket;

    QQueue<QVariant> readQueue;
};

#endif // JSONSOCKET_H
