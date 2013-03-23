#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <qjson/parser.h>
#include <QObject>
#include <QTcpSocket>
#include <QScopedPointer>
#include <QSharedPointer>

#include "board.h"

class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(int socketDescriptor, QSharedPointer<Board> board, QObject *parent = 0);

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

    QSharedPointer<Board> board;
};

#endif // CLIENTCONNECTION_H
