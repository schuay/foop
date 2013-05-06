#include <QTcpSocket>

#include "serverconnection.h"
#include "directionmessage.h"
#include "gameovermessage.h"
#include "jsonvariantsocket.h"
#include "message.h"
#include "messagefactory.h"
#include "QsLog.h"
#include "statemessage.h"
#include "identifymessage.h"

/**
 * @brief ServerConnection::ServerConnection
 * Creates a connection to the given parameters
 * @param host Hostname of the server != NULL
 * @param port Portnumber of the server > 0
 * @param parent Qt-element above
 */
ServerConnection::ServerConnection(QString host, int port, QObject *parent) :
    QObject(parent),
    host(host),
    port(port)
{
    qRegisterMetaType<BoardPtr>("BoardPtr");
}

/**
 * @brief ServerConnection::run
 * Try to connect to the server, runs
 * game if a connection could be created
 */
void ServerConnection::run()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    QSharedPointer<QTcpSocket> tcpSocket(new QTcpSocket());
    tcpSocket->connectToHost(host, port);

    if (!tcpSocket->waitForConnected()) {
        QLOG_ERROR() << tcpSocket->errorString();
        emit finished();
    }

    variantSocket.reset(new JsonVariantSocket(tcpSocket));

    connect(variantSocket.data(), SIGNAL(readChannelFinished()), this, SIGNAL(finished()));
    connect(variantSocket.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

/**
 * @brief ServerConnection::onDirectionChange
 * writes the choosen direction of the player to the
 * server
 * @param direction a valid direction of the snake
 */
void ServerConnection::onDirectionChange(Snake::Direction direction)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << direction;

    DirectionMessage directionMessage(direction);
    variantSocket->write(directionMessage.toVariant());
}

/**
 * @brief ServerConnection::onReadyRead
 * Reads the message from the server, and
 * choose the operation by the type of this
 * message
 *
 * valid messages are:
 *  GameOver: for the end of the game
 *  state: for all information about the game
 *  identify: for identifing the client (snake)
 */
void ServerConnection::onReadyRead()
{
    QVariant v = variantSocket->read();

    if (v.isNull()) {
        return;
    }

    /* Deserialize the message and emit the appropriate signal. */

    QSharedPointer<Message> message = MessageFactory::createMessage(v);

    if (message.isNull()) {
        QLOG_ERROR() << "Received message is null.";
        return;
    }

    switch (message->getType()) {
    case Message::MSG_GAMEOVER: {
            QSharedPointer<GameoverMessage> gameOverMessage = qSharedPointerCast<GameoverMessage>(message);
            emit gameOver(gameOverMessage->getWon());
            variantSocket->close();
            break;
        }
    case Message::MSG_STATE: {
            QSharedPointer<StateMessage> stateMessage = qSharedPointerCast<StateMessage>(message);
            emit newTurn(stateMessage->getId(), stateMessage->getBoard());
            break;
        }
    case Message::MSG_IDENTIFY: {
            QSharedPointer<IdentifyMessage> identifyMessage = qSharedPointerCast<IdentifyMessage>(message);
            emit setSnakeId(identifyMessage->getId());
            break;
        }
    default:
        QLOG_ERROR() << "The received message type is unknown:" << message->getType();
        return;
    }
}
