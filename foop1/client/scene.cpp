#include "scene.h"

#include "QsLog.h"
#include "QKeyEvent"

/* Temporary settings until we actually have a board from the server. */
#define WIDTH (32)
#define HEIGHT (32)

#define CELL_SEPARATOR (1)

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    board.reset(new Board(WIDTH, HEIGHT));

    for (int x = 0; x < board->getWidth(); x++) {
        for (int y = 0; y < board->getHeight(); y++) {
            CellItem *cellItem = new CellItem();
            cells.append(cellItem);
            addItem(cellItem);
        }
    }
}

void Scene::resize(const QSize &size)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << size;

    setSceneRect(QRectF(0, 0, size.width(), size.height()));

    const int maxXCellsize = size.width() / board->getWidth();
    const int maxYCellsize = size.height() / board->getHeight();
    const int cellsize = qMin(maxXCellsize, maxYCellsize);

    const int xOffset = (size.width() - board->getWidth() * cellsize) / 2;
    const int yOffset = (size.height() - board->getHeight() * cellsize) / 2;

    for (int i = 0; i < board->getWidth() * board->getHeight(); i++) {
        const int x = i / board->getWidth();
        const int y = i % board->getWidth();

        CellItem *cellItem = cells.at(i);
        cellItem->setRect(0, 0, cellsize - CELL_SEPARATOR, cellsize - CELL_SEPARATOR);
        cellItem->setPos(xOffset + x * cellsize, yOffset + y * cellsize);
    }
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
