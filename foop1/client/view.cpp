#include "view.h"

#include <QResizeEvent>

/**
 * @brief View::View
 * creates the view on the scene
 * @param parent Qt-element above
 */
View::View(QWidget *parent) :
    QGraphicsView(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(QFrame::NoFrame);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

/**
 * @brief View::createScene
 * Creates a new scene of the game
 * @return the new scene
 */
Scene *View::createScene()
{
    scene = new Scene(this);
    setScene(scene);
    scene->resize(size());
    return scene;
}

/**
 * @brief View::resizeEvent
 * resizes the gamefield
 * @param event Gets the resizing event
 */
void View::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    if (scene != NULL) {
        scene->resize(event->size());
    }
}
