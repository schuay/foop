#include "serverconnection.h"

#include <QTcpSocket>

#include "jsonvariantsocket.h"
#include "QsLog.h"

ServerConnection::ServerConnection(QString host, int port, QObject *parent) :
    QObject(parent),
    host(host),
    port(port)
{
}

void ServerConnection::run()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    QSharedPointer<QTcpSocket> tcpSocket(new QTcpSocket());
    tcpSocket->connectToHost(host, port);

    if (!tcpSocket->waitForConnected()) {
        QLOG_ERROR() << tcpSocket->errorString();
        emit finished();
    }

    variantSocket.reset(new JsonVariantSocket(tcpSocket));
}
