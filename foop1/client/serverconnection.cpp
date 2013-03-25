#include "serverconnection.h"

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
}
