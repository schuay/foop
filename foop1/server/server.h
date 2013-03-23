#ifndef SERVER_H
#define SERVER_H

#include <QScopedPointer>
#include <QTcpServer>

#include "game.h"

class Server : public QTcpServer
{
public:
    Server(QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);

private:
    QScopedPointer<Game> game;
};

#endif // SERVER_H
