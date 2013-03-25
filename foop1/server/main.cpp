#include <QCoreApplication>
#include <QScopedPointer>

#include "QsLog.h"
#include "QsLogDest.h"
#include "server.h"

#define PORT (16384)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QsLogging::Logger &logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::DebugLevel);

    QsLogging::DestinationPtr debugDestination(
        QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination.get());

    QScopedPointer<Server> server(new Server());
    server->listen(QHostAddress::Any, PORT);

    QLOG_INFO() << "Listening on port" << PORT;

    return a.exec();
}
