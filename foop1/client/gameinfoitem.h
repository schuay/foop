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
    void setWidth(int width);
    void setHeight(int height);
    void setPoints(QString points);
    int getHeight();
    void setPadding(QPoint);
    QPoint getPadding();

private:
    int width;
    int height;
    QScopedPointer<ColorScheme> colorScheme;
    QPoint padding;
    QGraphicsRectItem *rect;
    QMap<Snake::Priority, QGraphicsRectItem *> prioMap;
    QGraphicsSimpleTextItem *points;

private:
};

#endif // GAMEINFOITEM_H
