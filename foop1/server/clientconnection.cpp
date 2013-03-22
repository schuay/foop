#include "clientconnection.h"


#include "QsLog.h"

ClientConnection::ClientConnection(int socketDescriptor, QObject *parent) :
    QObject(parent), socketDescriptor(socketDescriptor)
{
}

void ClientConnection::process()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    tcpSocket.reset(new QTcpSocket(this));
    if (!tcpSocket->setSocketDescriptor(socketDescriptor)) {
        QLOG_ERROR() << tcpSocket->error();
        emit finished();
        return;
    }

    connect(tcpSocket.data(), SIGNAL(readyRead()), this, SLOT(read()));
    connect(tcpSocket.data(), SIGNAL(readChannelFinished()), this, SIGNAL(finished()));
}

void ClientConnection::read()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    QByteArray data = tcpSocket->readAll();
    QLOG_TRACE() << "Received:" << data;
}
