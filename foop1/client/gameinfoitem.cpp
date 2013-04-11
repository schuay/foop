#include "gameinfoitem.h"

#include <QBrush>
#include <QMap>
#include <QPainter>
#include <QPen>

GameInfoItem::GameInfoItem()
    : QGraphicsItemGroup()
{
    points = new QGraphicsSimpleTextItem();

    colorScheme.reset(new DefaultColorScheme());
    setPadding(QPoint(0, 0));

    rect = new QGraphicsRectItem();
    rect->setPos(0, 0);
    rect->setBrush(QBrush(Qt::white));
    rect->setPen(QPen(Qt::NoPen));
    addToGroup(rect);

    for (int i = Snake::PRI_LOWEST; i <= Snake::PRI_HIGHEST; ++i) {
        QGraphicsRectItem *rect = new QGraphicsRectItem();

        Snake::Priority prio = (Snake::Priority)i;

        rect->setBrush(QBrush(colorScheme->colorForPriority(prio)));
        rect->setPen(QPen(Qt::NoPen));

        prioMap[(Snake::Priority)i] = rect;

        addToGroup(rect);

    }

    points->setText("0");
    addToGroup(points);

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

int GameInfoItem::getHeight()
{
    return height;
}

void GameInfoItem::setPadding(QPoint padding)
{
    this->padding = padding;
}

QPoint GameInfoItem::getPadding()
{
    return padding;
}

void GameInfoItem::setPoints(QString points)
{
    this->points->setText(points);
}

void GameInfoItem::layout()
{
    /* TODO: Refactor this. It's a mixture of setting up the layout (placement) and the content, plus
     * there's a memory leak. */
    rect->setRect(0, 0, width, height);

    for (int i = Snake::PRI_LOWEST; i <= Snake::PRI_HIGHEST; ++i) {
        prioMap.value((Snake::Priority)i)->setRect(0, 0, height - padding.x() * 2, height - padding.y() * 2);
        prioMap.value((Snake::Priority)i)->setPos((width - Snake::PRI_HIGHEST * height) + i * height + padding.x(), padding.y());
    }
    QFont *newFont = new QFont();
    newFont->setPixelSize(getHeight() - padding.y() * 2);
    points->setFont(*newFont);
    points->setPos(padding.x(), padding.y());
}
