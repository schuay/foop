#include "statemessage.h"

#define KEY_BOARD ("board")
#define KEY_BODY ("body")
#define KEY_DIRECTION ("direction")
#define KEY_GROWTH ("growth")
#define KEY_HEIGHT ("height")
#define KEY_ID ("id")
#define KEY_PRIORITY ("priority")
#define KEY_SNAKES ("snakes")
#define KEY_WIDTH ("width")

/**
 * @brief StateMessage::StateMessage
 * creates a message about the current status of the
 * game with the information about the board and the snake id
 * @param board information about the playing board
 * @param id unique id of the snake
 */
StateMessage::StateMessage(QSharedPointer<Board> board, int id) :
    board(board), id(id)
{
}

/**
 * @brief StateMessage::StateMessage
 * creates the message about the current game status
 * from the incoming network-message-element. gets id
 * of the clients gamer snake, width/height of the board,
 * and the locations of all the snakes in the game
 * @param variant network-message with the information about
 * the game, != NULL
 */
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
        snake->pendingGrowth = snakeMapVariant.value(KEY_GROWTH).toInt();

        QList<QVariant> bodyListVariant = snakeMapVariant.value(KEY_BODY).toList();
        for (int i = 0; i < bodyListVariant.size(); i += 2) {
            QPoint p(bodyListVariant.at(i).toInt(), bodyListVariant.at(i + 1).toInt());
            snake->body.append(p);
        }

        board->snakes.append(snake);
    }
}

/**
 * @brief StateMessage::getType
 * returns the specific type of this message
 * @return the defined type of this message
 */
int StateMessage::getType() const
{
    return MSG_STATE;
}

/**
 * @brief StateMessage::getId
 * getting the id of the client's snake
 * @return unique id of the snake
 */
int StateMessage::getId() const
{
    return id;
}

/**
 * @brief StateMessage::getBoard
 * getting the board information of the game
 * @return the board
 */
QSharedPointer<Board> StateMessage::getBoard() const
{
    return board;
}

/**
 * @brief StateMessage::toVariant
 * packs all information of the clients snake and
 * other game information into a transferable
 * network-package for client/server communication
 * @return the transferable networking package with
 * the needed information about the game
 */
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
        snakeVariant.insert(KEY_GROWTH, snake->pendingGrowth);

        /* We'll take the easy way out for now and transmit each body point.
         * This can be optimized later on as necessary. */

        QVariantList bodyVariant;
        foreach(const QPoint & point, snake->getBody()) {
            /* QJson can't handle QPoints. */
            bodyVariant.append(point.x());
            bodyVariant.append(point.y());
        }
        snakeVariant.insert(KEY_BODY, bodyVariant);

        snakesVariant.append(snakeVariant);
    }
    boardVariant.insert(KEY_SNAKES, snakesVariant);

    v.insert(KEY_BOARD, boardVariant);

    return v;
}
