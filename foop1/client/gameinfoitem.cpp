#include "gameinfoitem.h"

#include <QBrush>
#include <QMap>
#include <QPainter>
#include <QPen>

#define PADDING (20)
#define PRIORITY_SIZE (32)
#define FONT_SIZE (24)

GameInfoItem::GameInfoItem(const ColorScheme *colorScheme)
    : QGraphicsItemGroup()
{
    font.setPixelSize(FONT_SIZE);

    points = new QGraphicsSimpleTextItem();
    points->setFont(font);
    addToGroup(points);

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
}

void GameInfoItem::layout()
{
    const int priorityWidth = PRIORITY_SIZE + PADDING;
    const int prioritySectionWidth = Snake::PRI_COUNT * priorityWidth;
    for (int i = 0; i < Snake::PRI_COUNT; i++) {
        priorityRects.at(i)->setPos(width - prioritySectionWidth + i * priorityWidth, PADDING);
    }

    points->setPos(PADDING, PADDING);
}
