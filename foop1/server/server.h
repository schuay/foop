#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
public:
    Server(QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H
