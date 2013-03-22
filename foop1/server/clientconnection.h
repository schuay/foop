#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <qjson/parser.h>
#include <QObject>
#include <QTcpSocket>
#include <QScopedPointer>

class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(int socketDescriptor, QObject *parent = 0);

signals:
    void finished();

public slots:
    void process();

private slots:
    void read();

private:
    const int socketDescriptor;
    QScopedPointer<QTcpSocket> tcpSocket;

    QByteArray buffer;

    QScopedPointer<QJson::Parser> parser;
};

#endif // CLIENTCONNECTION_H
