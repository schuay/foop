#ifndef JSONSOCKET_H
#define JSONSOCKET_H

#include <qjson/parser.h>
#include <qjson/serializer.h>
#include <QObject>
#include <QQueue>
#include <QScopedPointer>
#include <QTcpSocket>
#include <QVariant>

class JsonSocket : public QObject
{
    Q_OBJECT
public:
    JsonSocket(int socketDescriptor);

    QVariant read();
    void write(const QVariant &data);

signals:
    void readChannelFinished();
    void readyRead();

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
