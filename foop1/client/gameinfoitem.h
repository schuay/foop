#ifndef GAMEINFOITEM_H
#define GAMEINFOITEM_H

#include <QFont>
#include <QGraphicsItemGroup>

#include "colorscheme.h"
#include "snake.h"

#define GAME_INFO_HEIGHT (64)

/**
 * @brief The GameInfoItem class
 * Provides the graphic-qt-elements for the game field
 */
class GameInfoItem : public QGraphicsItemGroup
{
public:
    GameInfoItem(const ColorScheme *colorScheme);

    void setWidth(int width);
    void setPoints(int points);
    void setCurrentPriority(Snake::Priority priority);

private:
    void layout();

private:
    int width, currentPriority;

    QGraphicsSimpleTextItem *points, *pointsLabel, *priorityLabel;
    QGraphicsRectItem *currentPriorityRect;
    QList<QGraphicsRectItem *> priorityRects;
};

#endif // GAMEINFOITEM_H
