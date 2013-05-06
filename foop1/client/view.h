#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

#include "scene.h"

/**
 * @brief The View class
 * Provides the qt-view on the scene
 */
class View : public QGraphicsView
{
public:
    explicit View(QWidget *parent = 0);

    Scene *createScene();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Scene *scene;
};

#endif // VIEW_H
