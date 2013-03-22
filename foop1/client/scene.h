#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QScopedPointer>

#include "griditem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene(QObject *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *keyEvent);

private:
    void onDirectionPress(int dx, int dy);

private:
    QScopedPointer<GridItem> gridItem;
};

#endif // SCENE_H
