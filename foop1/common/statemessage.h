#ifndef STATEMESSAGE_H
#define STATEMESSAGE_H

#include <QSharedPointer>

#include "board.h"
#include "message.h"

class StateMessage : public Message
{
public:
    StateMessage(QSharedPointer<Board> board);

    int getType() const;
    QVariant toVariant() const;

private:
    QSharedPointer<Board> board;
};

#endif // STATEMESSAGE_H
