#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "scene.h"
#include "view.h"
#include "serverconnection.h"

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
    QThread *thread;
    ServerConnection *connection;
};

#endif // MAINWINDOW_H
