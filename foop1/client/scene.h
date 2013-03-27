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

#include "board.h"
#include "cellitem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene(QObject *parent = 0);

    void resize(const QSize &size);

signals:
    void directionChange(Snake::Direction direction);

protected:
    void keyPressEvent(QKeyEvent *keyEvent);

private:
    void onDirectionPress(Snake::Direction direction);

    /** Updates the displayed items to reflect the current board state.
     *  The board size is assumed to be constant. */
    void update();

    void growSnakeCells();

private:
    /* Note: Use scoped pointers for objects which are not
     * shared (its pointer is only stored in a single location),
     * and QSharedPointer<> for shared objects. */
    QScopedPointer<Board> board;

    /** Contains all elements of the actual playing field. */
    QGraphicsItemGroup *group;

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
};

#endif // SCENE_H
