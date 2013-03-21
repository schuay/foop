#include "mainwindow.h"
#include <QApplication>

#include "QsLog.h"
#include "QsLogDest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QsLogging::Logger &logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

    QsLogging::DestinationPtr debugDestination(
        QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination.get());

    MainWindow w;
    w.show();

    return a.exec();
}
