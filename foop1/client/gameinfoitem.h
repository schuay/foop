#ifndef GAMEINFOITEM_H
#define GAMEINFOITEM_H

#include <QGraphicsItemGroup>

#include "defaultcolorscheme.h"
#include "snake.h"

#define GAME_INFO_HEIGHT (64)

class GameInfoItem : public QGraphicsItemGroup
{
public:
    GameInfoItem();

    void layout();

    void setWidth(int width);

    void setPoints(QString points);

private:
    int width;

    QGraphicsSimpleTextItem *points;
    QMap<Snake::Priority, QGraphicsRectItem *> prioMap;

    QScopedPointer<ColorScheme> colorScheme;
};

#endif // GAMEINFOITEM_H
