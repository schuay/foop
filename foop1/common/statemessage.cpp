#include "statemessage.h"

#define KEY_BOARD ("board")

StateMessage::StateMessage(QSharedPointer<Board> board) :
    board(board)
{
}

int StateMessage::getType() const
{
    return MSG_STATE;
}

QVariant StateMessage::toVariant() const
{
    QVariantMap v;
    v.insert(KEY_TYPE, getType());
    v.insert(KEY_BOARD, board->toVariant());
    return v;
}
