#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>

#include "board.h"
#include "jsonsocket.h"

class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(int socketDescriptor, QSharedPointer<Board> board, QObject *parent = 0);

signals:
    void finished();

public slots:
    void process();
    void newTurn();

private slots:
    void onReadyRead();

private:
    const int socketDescriptor;

    /* This needs to be a scoped pointer (instead of just an object instance)
     * since we need to defer initialization until the object is running in its target thread. */
    QScopedPointer<JsonSocket> jsonSocket;

    QSharedPointer<Board> board;
};

#endif // CLIENTCONNECTION_H
