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
    void setPadding(QPoint);

private:
    int width, height;
    QPoint padding;

    QGraphicsSimpleTextItem *points;
    QGraphicsRectItem *rect;
    QMap<Snake::Priority, QGraphicsRectItem *> prioMap;

    QScopedPointer<ColorScheme> colorScheme;

private:
};

#endif // GAMEINFOITEM_H
