#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

#include "scene.h"

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
