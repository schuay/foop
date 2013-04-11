#include "gameinfoitem.h"

#include <QBrush>
#include <QMap>
#include <QPainter>
#include <QPen>

#define PADDING (20)
#define PRIORITY_SIZE (32)
#define FONT_SIZE (24)

GameInfoItem::GameInfoItem()
    : QGraphicsItemGroup()
{
    points = new QGraphicsSimpleTextItem();
    points->setText("0");
    addToGroup(points);

    colorScheme.reset(new DefaultColorScheme());

    for (int i = Snake::PRI_LOWEST; i <= Snake::PRI_HIGHEST; ++i) {
        QGraphicsRectItem *rect = new QGraphicsRectItem();

        Snake::Priority prio = (Snake::Priority)i;

        rect->setBrush(QBrush(colorScheme->colorForPriority(prio)));
        rect->setPen(QPen(Qt::NoPen));

        prioMap[(Snake::Priority)i] = rect;

        addToGroup(rect);
    }
}

void GameInfoItem::setWidth(int width)
{
    this->width = width;
    layout();
}

void GameInfoItem::setHeight(int height)
{
    this->height = height;
    layout();
}

void GameInfoItem::setPoints(QString points)
{
    this->points->setText(points);
}

void GameInfoItem::layout()
{
    /* TODO: Refactor this. It's a mixture of setting up the layout (placement) and the content, plus
     * there's a memory leak. */
    for (int i = 0; i < Snake::PRI_COUNT; ++i) {
        prioMap.value((Snake::Priority)i)->setRect(0, 0, PRIORITY_SIZE, PRIORITY_SIZE);
        prioMap.value((Snake::Priority)i)->setPos((width - Snake::PRI_HIGHEST * height) +
                i * height + PADDING, PADDING);
    }
    QFont *newFont = new QFont();
    newFont->setPixelSize(FONT_SIZE);
    points->setFont(*newFont);
    points->setPos(PADDING, PADDING);
}
