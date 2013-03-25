#ifndef MESSAGE_H
#define MESSAGE_H

#include "serializable.h"

#define KEY_TYPE ("type")

class Message : public Serializable
{
public:
    enum {
        MSG_DIRECTION,
        MSG_STATE
    };

    virtual int getType() const = 0;
};

#endif // MESSAGE_H
