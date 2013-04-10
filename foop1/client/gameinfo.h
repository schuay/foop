#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <snake.h>
#include "defaultcolorscheme.h"

#include <QGraphicsRectItem>

class GameInfo : public QGraphicsItemGroup
{

public:
    GameInfo();
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

#endif // GAMEINFO_H
