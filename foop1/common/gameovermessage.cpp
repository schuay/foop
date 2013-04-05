#define KEY_SCORE ("score")
#define KEY_WON ("won")

#include "gameovermessage.h"


GameoverMessage::GameoverMessage(int score, bool won) :
    score(score),
    won(won)
{
}

GameoverMessage::GameoverMessage(const QVariant &variant)
{
    QMap<QString, QVariant> mapVariant = variant.toMap();
    score = mapVariant.value(KEY_SCORE).toInt();
    won = mapVariant.value(KEY_WON).toBool();
}

QVariant GameoverMessage::toVariant() const
{
    QVariantMap v;
    v.insert(KEY_TYPE, getType());
    v.insert(KEY_SCORE, score);
    v.insert(KEY_WON, won);

    return v;
}

int GameoverMessage::getType() const
{
    return MSG_GAMEOVER;
}

