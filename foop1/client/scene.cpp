#include "scene.h"

#include <QKeyEvent>
#include <QMessageBox>

#include "cellitem.h"
#include "defaultcolorscheme.h"
#include "gameinfoitem.h"
#include "QsLog.h"

#define INFO_REL_HEIGHT (0.15)

#define CELL_SEPARATOR (1)

/**
 * @brief Scene::Scene
 * Creates and inits the game elements
 * @param parent Qt-element above
 */
Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    colorScheme.reset(new DefaultColorScheme());
    board = QSharedPointer<Board>(new Board(BOARD_WIDTH, BOARD_HEIGHT));

    gameInfo = new GameInfoItem(colorScheme.data());
    addItem(gameInfo);

    group = new QGraphicsItemGroup();
    addItem(group);

    //Adding cells to the scene
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

/**
 * @brief Scene::resize
 * Resizes the game elements
 * @param size new size
 */
void Scene::resize(const QSize &size)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << size;

    setSceneRect(QRectF(0, 0, size.width(), size.height()));

    const int gameHeight = size.height() - GAME_INFO_HEIGHT;

    gameInfo->setWidth(size.width());

    //Setting the maximum of one cellsize by height/width of the board
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

/**
 * @brief Scene::updateScene
 * Creates graphic-elements (e.g. the snakes) on the game field and
 * Registers changes on the gamefield by calling this function
 * and display it
 */
void Scene::updateScene()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    /* How many snake cells do we need in total? */
    //bodyMassIndex >= 0
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

/**
 * @brief Scene::growSnakeCells
 * Grows size of snake per one cell
 */
void Scene::growSnakeCells()
{
    CellItem *cellItem = new CellItem();
    cellItem->setCellSize(cellsize);
    snakecells.append(cellItem);
    group->addToGroup(cellItem);
}

/**
 * @brief Scene::onDirectionPress
 * gets new direction input and sends
 * the associated signal for handling
 * @param direction A possible driving
 * direction of the snake
 */
void Scene::onDirectionPress(Snake::Direction direction)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << direction;

    emit directionChange(direction);
}

/**
 * @brief Scene::keyPressEvent
 * Registers the pressing of key, and calling a
 * handling function if the key is okay
 * key can be: left, right, up or down
 *
 * @param keyEvent that is called during the
 * game
 */
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

/**
 * @brief Scene::onNewTurn
 * by every new turn the scene is updated, to
 * show the new state of the game
 * @param id Id of the snake >= 0
 * @param board Current playing board != NULL
 */
void Scene::onNewTurn(int id, BoardPtr board)
{
    QLOG_TRACE() << __PRETTY_FUNCTION__ << id;

    this->board = board;
    updateScene();
}

/**
 * @brief Scene::onGameOver
 * Shows a qt-messagebox, when the game
 * is finished for you. you can win or loose
 * @param won information about the game-end
 * TRUE if you lost, FALSE if you won
 */
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

/**
 * @brief Scene::setSnakeId
 * Sets the unique id >= 0 of the snake
 * @param id unique id, >= 0
 */
void Scene::setSnakeId(int id)
{
    snakeId = id;
}
