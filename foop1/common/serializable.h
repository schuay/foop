#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QVariant>

class Serializable
{
public:
    virtual QVariant toVariant() const = 0;
};

#endif // SERIALIZABLE_H
