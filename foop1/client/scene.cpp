#include "scene.h"

#include <QKeyEvent>
#include <QMessageBox>

#include "cellitem.h"
#include "defaultcolorscheme.h"
#include "gameinfoitem.h"
#include "QsLog.h"

/* Temporary settings until we actually have a board from the server. */
#define WIDTH (32)
#define HEIGHT (32)

#define INFO_REL_HEIGHT (0.15)

#define CELL_SEPARATOR (1)

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    colorScheme.reset(new DefaultColorScheme());
    board = QSharedPointer<Board>(new Board(WIDTH, HEIGHT));

    gameInfo = new GameInfoItem(colorScheme.data());
    addItem(gameInfo);

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

    updateScene();
}

void Scene::resize(const QSize &size)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << size;

    setSceneRect(QRectF(0, 0, size.width(), size.height()));

    const int gameHeight = size.height() - GAME_INFO_HEIGHT;

    gameInfo->setWidth(size.width());

    const int maxXCellsize = size.width() / board->getWidth();
    const int maxYCellsize = gameHeight / board->getHeight();

    cellsize = qMin(maxXCellsize, maxYCellsize);

    foreach(CellItem * cellItem, gridcells) {
        cellItem->setCellSize(cellsize);
    }

    foreach(CellItem * cellItem, snakecells) {
        cellItem->setCellSize(cellsize);
    }

    const int xOffset = (size.width() - board->getWidth() * cellsize) / 2;
    const int yOffset = GAME_INFO_HEIGHT + (gameHeight - board->getHeight() * cellsize) / 2;

    group->setPos(xOffset, yOffset);
}

void Scene::updateScene()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    /* How many snake cells do we need in total? */
    int bodyMassIndex = 0;
    QSharedPointer<Snake> mySnake;

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

        if (snake->getId() == snakeId) {
            mySnake = snake;
        }

    }

    for (; bodyMassIndex < snakecells.size(); bodyMassIndex++) {
        snakecells.at(bodyMassIndex)->setVisible(false);
    }

    if (!mySnake.isNull()) {
        gameInfo->setPoints(mySnake->getPoints());
        gameInfo->setCurrentPriority(mySnake->getPriority());
    }
}

void Scene::growSnakeCells()
{
    CellItem *cellItem = new CellItem();
    cellItem->setCellSize(cellsize);
    snakecells.append(cellItem);
    group->addToGroup(cellItem);
}

void Scene::onDirectionPress(Snake::Direction direction)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << direction;

    emit directionChange(direction);
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

void Scene::onNewTurn(int id, BoardPtr board)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << id;

    this->board = board;
    updateScene();
}

void Scene::onGameOver(bool won)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << won;

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(QString("Game Over. You %1!").arg(won ? "WON" : "lost"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void Scene::setSnakeId(int id)
{
    snakeId = id;
}
