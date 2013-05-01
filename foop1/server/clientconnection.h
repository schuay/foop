#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>

#include "board.h"
#include "abstractvariantsocket.h"

/**
 * The ClientConnection to be able to communicate with a client via sockets
 */
class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(int socketDescriptor, QSharedPointer<Board> board, QObject *parent = 0);
    QSharedPointer<Snake> getSnake();
    void gameOver();

signals:
    void finished();

public slots:
    void run();
    void newTurn();

private slots:
    void onReadyRead();
    void onReadChannelFinished();

private:
    const int socketDescriptor;

    /* This needs to be a scoped pointer (instead of just an object instance)
     * since we need to defer initialization until the object is running in its target thread. */
    QScopedPointer<AbstractVariantSocket> variantSocket;

    QSharedPointer<Board> board;
    QSharedPointer<Snake> snake;
};

#endif // CLIENTCONNECTION_H
