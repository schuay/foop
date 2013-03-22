#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>

class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(QObject *parent = 0);

signals:
    void finished();

public slots:
    void process();

};

#endif // CLIENTCONNECTION_H
