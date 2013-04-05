#ifndef STATEMESSAGE_H
#define STATEMESSAGE_H

#include <QSharedPointer>

#include "board.h"
#include "message.h"

class StateMessage : public Message
{
public:
    StateMessage(QSharedPointer<Board> board, int id);
    StateMessage(const QVariant &variant);

    int getType() const;
    int getId() const;
    QSharedPointer<Board> getBoard() const;

    QVariant toVariant() const;

private:
    int id; /**< The ID of the owner's snake. */
    QSharedPointer<Board> board;
};

#endif // STATEMESSAGE_H
