#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QScopedPointer>

#include "abstractvariantsocket.h"
#include "snake.h"

class ServerConnection : public QObject
{
    Q_OBJECT
public:
    explicit ServerConnection(QString host, int port, QObject *parent = 0);

signals:
    void finished();
    void newTurn();

public slots:
    void run();
    void onDirectionChange(Snake::Direction direction);

private:
    const QString host;
    const int port;

    QScopedPointer<AbstractVariantSocket> variantSocket;

};

#endif // SERVERCONNECTION_H
