#ifndef GAMEINFOITEM_H
#define GAMEINFOITEM_H

#include <QGraphicsItemGroup>

#include "defaultcolorscheme.h"
#include "snake.h"

class GameInfoItem : public QGraphicsItemGroup
{
public:
    GameInfoItem();

    void layout();

    void setHeight(int height);
    void setWidth(int width);

    void setPoints(QString points);

private:
    int width, height;

    QGraphicsSimpleTextItem *points;
    QMap<Snake::Priority, QGraphicsRectItem *> prioMap;

    QScopedPointer<ColorScheme> colorScheme;

private:
};

#endif // GAMEINFOITEM_H
