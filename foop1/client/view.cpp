#include "view.h"

View::View(QWidget *parent) :
    QGraphicsView(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(QFrame::NoFrame);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

Scene *View::createScene()
{
    scene = new Scene(this);
    setScene(scene);
    return scene;
}

void View::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
}
