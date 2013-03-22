#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene(QObject *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *keyEvent);
};

#endif // SCENE_H
