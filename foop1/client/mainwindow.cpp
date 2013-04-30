#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPointer>

#include "newgamedialog.h"
#include "QsLog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Init private Members to 0 for checking
    this->thread = 0;
    this->connection = 0;

    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(onQuit()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(onNewGame()));

    view = new View(this);
    scene = view->createScene();

    setCentralWidget(view);
}

void MainWindow::onNewGame()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    /* Start the connection dialog. */

    QPointer<NewGameDialog> dialog(new NewGameDialog(this));
    const int ret = dialog->exec();

    const QString host = dialog->host();
    const int port = dialog->port();

    delete dialog;

    if (ret != QDialog::Accepted) {
        return;
    }

    /* Clean up the old connection. */

    if (thread != NULL) {
        thread->disconnect();
        thread->exit();
        thread->terminate();
        connection->disconnect();

        thread = NULL;
        connection = NULL;
    }

    /* Start the server connection thread. This will be moved to
     * the 'New Game...' menu a little later. We will also need to
     * terminate and clean up left over old connections. */

    thread = new QThread();

    connection = new ServerConnection(host, port);
    connection->moveToThread(thread);

    qRegisterMetaType<Snake::Direction>("Snake::Direction");
    connect(scene, SIGNAL(directionChange(Snake::Direction)),
            connection, SLOT(onDirectionChange(Snake::Direction)));

    connect(connection, SIGNAL(newTurn(int, BoardPtr)),
            scene, SLOT(onNewTurn(int, BoardPtr)));
    connect(connection, SIGNAL(gameOver(bool)),
            scene, SLOT(onGameOver(bool)));
    connect(connection, SIGNAL(setSnakeId(int)),
            scene, SLOT(setSnakeId(int)));

    connect(thread, SIGNAL(started()), connection, SLOT(run()));
    connect(connection, SIGNAL(finished()), thread, SLOT(quit()));
    connect(connection, SIGNAL(finished()), connection, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), this, SLOT(onThreadFinished()));

    thread->start();
}

void MainWindow::onThreadFinished()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    thread = NULL;
    connection = NULL;
}

void MainWindow::onQuit()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
