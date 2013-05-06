#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "scene.h"
#include "view.h"
#include "serverconnection.h"

/**
 *  mainwindow provides and creates the elements of
 *  the clientside-interface and also it starts
 *  the game of a new-game-dialog
 */

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

private slots:
    void onThreadFinished();

private:
    Ui::MainWindow *ui;
    Scene *scene;
    View *view;
    QThread *thread;
    ServerConnection *connection;
};

#endif // MAINWINDOW_H
