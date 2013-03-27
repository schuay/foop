#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "scene.h"
#include "view.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onQuit();
    void onNewGame();

private:
    Ui::MainWindow *ui;
    Scene *scene;
    View *view;
};

#endif // MAINWINDOW_H
