#include "server.h"

#include <QThread>

#include "clientconnection.h"
#include "QsLog.h"

#define WIDTH (32)
#define HEIGHT (32)

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    game.reset(new Game(WIDTH, HEIGHT));
}

void Server::incomingConnection(int socketDescriptor)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << socketDescriptor;

    QThread *thread = new QThread();

    ClientConnection *connection = new ClientConnection(socketDescriptor, game->getBoard());
    connection->moveToThread(thread);

    connect(game.data(), SIGNAL(newTurn()), connection, SLOT(newTurn()));

    connect(thread, SIGNAL(started()), connection, SLOT(process()));
    connect(connection, SIGNAL(finished()), thread, SLOT(quit()));
    connect(connection, SIGNAL(finished()), connection, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
