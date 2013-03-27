#include "board.h"

#define KEY_HEIGHT ("height")
#define KEY_SNAKES ("snakes")
#define KEY_WIDTH ("width")

Board::Board(int width, int height) :
    width(width),
    height(height)
{
    /* TODO: Temp. */

    snakes.append(QSharedPointer<Snake>(new Snake()));
    snakes.append(QSharedPointer<Snake>(new Snake()));
    snakes.append(QSharedPointer<Snake>(new Snake()));
}

int Board::getWidth() const
{
    return width;
}

int Board::getHeight() const
{
    return height;
}

QList<QSharedPointer<Snake> > Board::getSnakes() const
{
    return snakes;
}

QVariant Board::toVariant() const
{
    QVariantMap map;
    map.insert(KEY_WIDTH, width);
    map.insert(KEY_HEIGHT, height);

    QVariantList list;
    for (int i = 0; i < snakes.size(); i++) {
        list.append(snakes.at(i)->toVariant());
    }
    map.insert(KEY_SNAKES, list);

    return map;
}
