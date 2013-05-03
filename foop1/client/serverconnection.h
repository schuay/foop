#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QScopedPointer>

#include "abstractvariantsocket.h"
#include "board.h"
#include "snake.h"

class ServerConnection : public QObject
{
    Q_OBJECT
public:
    explicit ServerConnection(QString host, int port, QObject *parent = 0);

    void close();

signals:
    void finished();
    void newTurn(int id, BoardPtr board);
    void gameOver(bool won);
    void setSnakeId(int);
public slots:
    void run();
    void onDirectionChange(Snake::Direction direction);
    void onReadyRead();

private:
    const QString host;
    const int port;

    QScopedPointer<AbstractVariantSocket> variantSocket;

};

#endif // SERVERCONNECTION_H
