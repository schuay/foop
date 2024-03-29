#include "server.h"

#include <QThread>
#include <QSignalMapper>

#include "clientconnection.h"
#include "QsLog.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    game.reset(new Game(BOARD_WIDTH, BOARD_HEIGHT));
}

void Server::incomingConnection(int socketDescriptor)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << socketDescriptor;

    QThread *thread = new QThread();

    ClientConnection *connection = new ClientConnection(socketDescriptor, game->getBoard());

    game->registerConnection(connection);
    connection->moveToThread(thread);

    connect(game.data(), SIGNAL(newTurn()), connection, SLOT(newTurn()));

    connect(thread, SIGNAL(started()), connection, SLOT(run()));
    connect(connection, SIGNAL(finished()), thread, SLOT(quit()));
    connect(connection, SIGNAL(finished()), connection, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
