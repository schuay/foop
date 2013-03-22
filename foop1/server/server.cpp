#include "server.h"

#include "QsLog.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
}

void Server::incomingConnection(int socketDescriptor)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << socketDescriptor;
}
