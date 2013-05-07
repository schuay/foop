#define KEY_SCORE ("score")
#define KEY_WON ("won")

#include "gameovermessage.h"

/**
 * @brief GameoverMessage::GameoverMessage
 * creates a message from server to client about
 * the exit-status of the played game
 * @param score, score of the player >= 0
 * @param won, TRUE if player has won the game,
 * FALSE if player lost the game
 */
GameoverMessage::GameoverMessage(int score, bool won) :
    score(score),
    won(won)
{
}

/**
 * @brief GameoverMessage::GameoverMessage
 * retrieving score and won-state of the incoming message
 * @param variant incoming packed message from the server != NULL
 */
GameoverMessage::GameoverMessage(const QVariant &variant)
{
    QMap<QString, QVariant> mapVariant = variant.toMap();
    score = mapVariant.value(KEY_SCORE).toInt();
    won = mapVariant.value(KEY_WON).toBool();
}

/**
 * @brief GameoverMessage::toVariant
 * packs the gameinformation into a qvariant for
 * transfering
 * @return the packed qvariant element, that includes
 * score and won-state of the game
 */
QVariant GameoverMessage::toVariant() const
{
    QVariantMap v;
    v.insert(KEY_TYPE, getType());
    v.insert(KEY_SCORE, score);
    v.insert(KEY_WON, won);

    return v;
}

/**
 * @brief GameoverMessage::getType
 * returns the specific type of this message
 * @return the defined type of this message
 */
int GameoverMessage::getType() const
{
    return MSG_GAMEOVER;
}

/**
 * @brief GameoverMessage::getWon
 * getting the exit-state of the current game
 * @return TRUE if the player won, else FALSE
 */
bool GameoverMessage::getWon() const
{
    return won;
}
