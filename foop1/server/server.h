#ifndef SERVER_H
#define SERVER_H

#include <QScopedPointer>
#include <QTcpServer>

#include "game.h"

/**
 * The Server which handles the connections.
*/
class Server : public QTcpServer
{
public:
    Server(QObject *parent = 0);

protected:
    /**
     * Handles incoming connection requests
     *
     * In:
     *  int socketDescriptor: the socket descriptor
    */
    void incomingConnection(int socketDescriptor);

private:
    QScopedPointer<Game> game;
};

#endif // SERVER_H
