#ifndef SCENE_H
#define SCENE_H

/* File layout is as follows:
 *
 * Includes with <>
 * Includes with ""
 * Class forward declarations, usings, ...
 *
 * class ...
 * {
 * public:
 * protected:
 * private:
 * }
 *
 * Functions and variables each go into a separate section
 * (note the two private sections below).
 */

#include <QGraphicsScene>
#include <QScopedPointer>
#include <QSharedPointer>

#include "board.h"
#include "colorscheme.h"

class CellItem;
class GameInfoItem;
class QGraphicsItemGroup;

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene(QObject *parent = 0);

    void resize(const QSize &size);

signals:
    void directionChange(Snake::Direction direction);

public slots:
    void onNewTurn(int id, BoardPtr board);
    void onGameOver(bool won);

protected:
    void keyPressEvent(QKeyEvent *keyEvent);

private:
    void onDirectionPress(Snake::Direction direction);

    /** Updates the displayed items to reflect the current board state.
     *  The board size is assumed to be constant. */
    void updateScene();

    void growSnakeCells();

private:
    QSharedPointer<Board> board;

    /** Contains all elements of the actual playing field. */
    QGraphicsItemGroup *group;

    /** Contains the information area. */
    GameInfoItem *gameInfo;

    /** The current side length of a cell. */
    int cellsize;

    /* The cell items which make up the main game area. Note that these do
     * *not* need to be freed, because a scene deletes all of its items
     * in its destructor.
     */

    /** Grid cells are placed once and then only touched if the screen is resized. */
    QList<CellItem *> gridcells;

    /** Snake cells are reusable items which make up the snake bodies. This list
     *  can grow or shrink dynamically. */
    QList<CellItem *> snakecells;

    /** The currently selected direction of the snake. Used to prevent sending
     *  unnecessary direction change messages to the server. */
    Snake::Direction direction;

    QScopedPointer<ColorScheme> colorScheme;
};

#endif // SCENE_H
