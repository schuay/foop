#ifndef GAMEINFOITEM_H
#define GAMEINFOITEM_H

#include <QFont>
#include <QGraphicsItemGroup>

#include "colorscheme.h"
#include "snake.h"

#define GAME_INFO_HEIGHT (64)

class GameInfoItem : public QGraphicsItemGroup
{
public:
    GameInfoItem(const ColorScheme *colorScheme);

    void setWidth(int width);
    void setPoints(int points);

private:
    void layout();

private:
    int width;

    QFont font;
    QGraphicsSimpleTextItem *points;
    QList<QGraphicsRectItem *> priorityRects;
};

#endif // GAMEINFOITEM_H
