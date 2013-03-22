#include "clientconnection.h"

#include "QsLog.h"

ClientConnection::ClientConnection(QObject *parent) :
    QObject(parent)
{
}

void ClientConnection::process()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    emit finished();
}
