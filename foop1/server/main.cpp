#include <QCoreApplication>

#include "QsLog.h"
#include "QsLogDest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QsLogging::Logger &logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

    QsLogging::DestinationPtr debugDestination(
        QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination.get());

    return a.exec();
}
