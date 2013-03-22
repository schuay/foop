#include "server.h"

#include <QThread>

#include "clientconnection.h"
#include "QsLog.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
}

void Server::incomingConnection(int socketDescriptor)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << socketDescriptor;

    QThread *thread = new QThread();

    ClientConnection *connection = new ClientConnection(socketDescriptor);
    connection->moveToThread(thread);

    connect(thread, SIGNAL(started()), connection, SLOT(process()));
    connect(connection, SIGNAL(finished()), thread, SLOT(quit()));
    connect(connection, SIGNAL(finished()), connection, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
