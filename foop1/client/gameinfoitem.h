#ifndef GAMEINFOITEM_H
#define GAMEINFOITEM_H

#include <QFont>
#include <QGraphicsItemGroup>

#include "defaultcolorscheme.h"
#include "snake.h"

#define GAME_INFO_HEIGHT (64)

class GameInfoItem : public QGraphicsItemGroup
{
public:
    GameInfoItem();

    void setWidth(int width);

    void setPoints(QString points);

private:
    void layout();

private:
    int width;

    QFont font;
    QGraphicsSimpleTextItem *points;
    QMap<Snake::Priority, QGraphicsRectItem *> prioMap;

    QScopedPointer<ColorScheme> colorScheme;
};

#endif // GAMEINFOITEM_H
