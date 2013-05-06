#include <QApplication>

#include "mainwindow.h"
#include "QsLog.h"
#include "QsLogDest.h"

/**
 * @brief main Starts the game for the player on the client side,
 * no input parameters are needed
 * @return Standard Return-Code
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Get the logger and set the Log-Level
    QsLogging::Logger &logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::DebugLevel);

    QsLogging::DestinationPtr debugDestination(
        QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination.get());

    MainWindow w;
    w.show();

    return a.exec();
}
