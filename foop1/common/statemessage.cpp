#include "statemessage.h"

#define KEY_BOARD ("board")
#define KEY_DIRECTION ("direction")
#define KEY_HEIGHT ("height")
#define KEY_ID ("id")
#define KEY_PRIORITY ("priority")
#define KEY_SNAKES ("snakes")
#define KEY_WIDTH ("width")

StateMessage::StateMessage(QSharedPointer<Board> board, int id) :
    board(board), id(id)
{
}

StateMessage::StateMessage(const QVariant &variant)
{
    QMap<QString, QVariant> mapVariant = variant.toMap();

    id = mapVariant.value(KEY_ID).toInt();

    QMap<QString, QVariant> boardVariant = mapVariant.value(KEY_BOARD).toMap();

    const int width = boardVariant.value(KEY_WIDTH).toInt();
    const int height = boardVariant.value(KEY_HEIGHT).toInt();

    board = QSharedPointer<Board>(new Board(width, height));

    QList<QVariant> snakesVariant = boardVariant.value(KEY_SNAKES).toList();
    foreach(const QVariant & snakeVariant, snakesVariant) {
        QMap<QString, QVariant> snakeMapVariant = snakeVariant.toMap();

        QSharedPointer<Snake> snake(new Snake(snakeMapVariant.value(KEY_ID).toInt()));
        snake->priority = (Snake::Priority)snakeMapVariant.value(KEY_PRIORITY).toInt();
        snake->direction = (Snake::Direction)snakeMapVariant.value(KEY_DIRECTION).toInt();

        board->snakes.append(snake);
    }
}

int StateMessage::getType() const
{
    return MSG_STATE;
}

int StateMessage::getId() const
{
    return id;
}

QSharedPointer<Board> StateMessage::getBoard() const
{
    return board;
}

QVariant StateMessage::toVariant() const
{
    QVariantMap v;
    v.insert(KEY_TYPE, getType());
    v.insert(KEY_ID, id);

    QVariantMap boardVariant;
    boardVariant.insert(KEY_WIDTH, board->width);
    boardVariant.insert(KEY_HEIGHT, board->height);

    QVariantList snakesVariant;
    foreach(QSharedPointer<Snake> snake, board->snakes) {
        QVariantMap snakeVariant;
        snakeVariant.insert(KEY_ID, snake->id);
        snakeVariant.insert(KEY_PRIORITY, snake->priority);
        snakeVariant.insert(KEY_DIRECTION, snake->direction);

        /* TODO: Body. */

        snakesVariant.append(snakeVariant);
    }
    boardVariant.insert(KEY_SNAKES, snakesVariant);

    v.insert(KEY_BOARD, boardVariant);

    return v;
}
