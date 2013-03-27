#include "scene.h"

#include <QKeyEvent>

#include "defaultcolorscheme.h"
#include "QsLog.h"

/* Temporary settings until we actually have a board from the server. */
#define WIDTH (32)
#define HEIGHT (32)

#define CELL_SEPARATOR (1)

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    colorScheme.reset(new DefaultColorScheme());
    board.reset(new Board(WIDTH, HEIGHT));

    group = new QGraphicsItemGroup();
    addItem(group);

    for (int x = 0; x < board->getWidth(); x++) {
        for (int y = 0; y < board->getHeight(); y++) {
            CellItem *cellItem = new CellItem();
            cellItem->setBoardPosition(x, y);
            gridcells.append(cellItem);
            group->addToGroup(cellItem);
        }
    }

    update();
}

void Scene::resize(const QSize &size)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << size;

    setSceneRect(QRectF(0, 0, size.width(), size.height()));

    const int maxXCellsize = size.width() / board->getWidth();
    const int maxYCellsize = size.height() / board->getHeight();
    const int cellsize = qMin(maxXCellsize, maxYCellsize);

    foreach(CellItem * cellItem, gridcells) {
        cellItem->setCellSize(cellsize);
    }

    foreach(CellItem * cellItem, snakecells) {
        cellItem->setCellSize(cellsize);
    }

    const int xOffset = (size.width() - board->getWidth() * cellsize) / 2;
    const int yOffset = (size.height() - board->getHeight() * cellsize) / 2;

    group->setPos(xOffset, yOffset);
}

void Scene::update()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    /* How many snake cells do we need in total? */
    int bodyMassIndex = 0;

    foreach(QSharedPointer<Snake> snake, board->getSnakes()) {
        QColor color = colorScheme->colorForPriority(snake->getPriority());

        foreach(const QPoint & p, snake->getBody()) {
            if (bodyMassIndex + 1 > snakecells.size()) {
                growSnakeCells();
            }

            CellItem *cellItem = snakecells.at(bodyMassIndex);

            cellItem->setBrush(QBrush(color));
            cellItem->setBoardPosition(p.x(), p.y());
            cellItem->setVisible(true);

            bodyMassIndex++;
        }
    }

    for (; bodyMassIndex < snakecells.size(); bodyMassIndex++) {
        snakecells.at(bodyMassIndex)->setVisible(false);
    }
}

void Scene::growSnakeCells()
{
    CellItem *cellItem = new CellItem();
    snakecells.append(cellItem);
    group->addToGroup(cellItem);
}

void Scene::onDirectionPress(Snake::Direction direction)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << direction;

    if (direction != this->direction) {
        this->direction = direction;
        emit directionChange(direction);
    }
}

void Scene::keyPressEvent(QKeyEvent *keyEvent)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << keyEvent->key();

    switch (keyEvent->key()) {
    case Qt::Key_Left:
        onDirectionPress(Snake::DIR_LEFT);
        break;
    case Qt::Key_Right:
        onDirectionPress(Snake::DIR_RIGHT);
        break;
    case Qt::Key_Up:
        onDirectionPress(Snake::DIR_UP);
        break;
    case Qt::Key_Down:
        onDirectionPress(Snake::DIR_DOWN);
        break;
    default:
        break;
    }
}
