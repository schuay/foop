#include "board.h"


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

QVariant Board::toVariant() const
{
    QVariantMap map;
    map.insert("width", width);
    map.insert("height", height);

    QVariantList list;
    for (int i = 0; i < snakes.size(); i++) {
        list.append(snakes.at(i)->toVariant());
    }
    map.insert("snakes", list);

    return map;
}
