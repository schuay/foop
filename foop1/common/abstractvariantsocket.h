#ifndef ABSTRACTVARIANTSOCKET_H
#define ABSTRACTVARIANTSOCKET_H

#include <QObject>
#include <QVariant>

class AbstractVariantSocket : public QObject
{
    Q_OBJECT
public:
    virtual QVariant read() = 0;
    virtual void write(const QVariant &data) = 0;

signals:
    void readChannelFinished();
    void readyRead();
};

#endif // ABSTRACTVARIANTSOCKET_H
