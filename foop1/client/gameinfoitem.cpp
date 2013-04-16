#include "gameinfoitem.h"

#include <QBrush>
#include <QPen>

#define PADDING (20)
#define CURRENT_PRIORITY_PADDING (2)
#define PRIORITY_SIZE (16)
#define PRIORITY_PADDING (8)
#define FONT_SIZE (24)
#define FONT_SIZE_LABEL (16)

GameInfoItem::GameInfoItem(const ColorScheme *colorScheme)
    : QGraphicsItemGroup()
{
    QFont font;
    font.setPixelSize(FONT_SIZE);
    font.setBold(true);

    points = new QGraphicsSimpleTextItem();
    points->setFont(font);
    addToGroup(points);

    font.setPixelSize(FONT_SIZE_LABEL);
    font.setBold(false);

    pointsLabel = new QGraphicsSimpleTextItem();
    pointsLabel->setFont(font);
    pointsLabel->setText("POINTS");
    addToGroup(pointsLabel);

    priorityLabel = new QGraphicsSimpleTextItem();
    priorityLabel->setFont(font);
    priorityLabel->setText("PRIORITIES");
    addToGroup(priorityLabel);

    currentPriorityRect = new QGraphicsRectItem();
    currentPriorityRect->setRect(0, 0, PRIORITY_SIZE + 2 * CURRENT_PRIORITY_PADDING,
                                 PRIORITY_SIZE + 2 * CURRENT_PRIORITY_PADDING);
    currentPriorityRect->setBrush(QBrush(Qt::black));
    currentPriorityRect->setPen(QPen(Qt::NoPen));
    addToGroup(currentPriorityRect);

    for (int i = 0; i < Snake::PRI_COUNT; i++) {
        QGraphicsRectItem *rect = new QGraphicsRectItem();
        rect->setRect(0, 0, PRIORITY_SIZE, PRIORITY_SIZE);
        rect->setBrush(QBrush(colorScheme->colorForPriority((Snake::Priority)i)));
        rect->setPen(QPen(Qt::NoPen));

        priorityRects.append(rect);

        addToGroup(rect);
    }
}

void GameInfoItem::setWidth(int width)
{
    this->width = width;
    layout();
}

void GameInfoItem::setPoints(int points)
{
    this->points->setText(QString::number(points));
    layout();
}

void GameInfoItem::setCurrentPriority(Snake::Priority priority)
{
    this->currentPriority = priority;
    layout();
}

void GameInfoItem::layout()
{
    const int priorityWidth = PRIORITY_SIZE + PRIORITY_PADDING;
    const int prioritySectionWidth = Snake::PRI_COUNT * priorityWidth;

    priorityLabel->setPos(width - prioritySectionWidth, PADDING - FONT_SIZE_LABEL);
    for (int i = 0; i < Snake::PRI_COUNT; i++) {
        priorityRects.at(i)->setPos(width - prioritySectionWidth + i * priorityWidth, PADDING);
    }
    currentPriorityRect->setPos(width - prioritySectionWidth +
                                currentPriority * priorityWidth - CURRENT_PRIORITY_PADDING,
                                PADDING - CURRENT_PRIORITY_PADDING);

    pointsLabel->setPos(PADDING, PADDING - FONT_SIZE_LABEL);
    points->setPos(PADDING, PADDING);
}
