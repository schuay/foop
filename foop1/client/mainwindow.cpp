#include <QPointer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newgamedialog.h"
#include "QsLog.h"

/**
 * @brief MainWindow::MainWindow Inits
 * and creates the interface elements and
 * also the connection and thread that is used
 * by the game
 *
 * connection and thread are NULL if there is
 * no open game for this client
 *
 * @param parent The parent-qt-element
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->thread = NULL;
    this->connection = NULL;

    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(onQuit()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(onNewGame()));

    view = new View(this);
    scene = view->createScene();

    setCentralWidget(view);
}

/**
 * @brief MainWindow::onNewGame shows the
 * new-game-dialog, closes the old game if
 * its not finished yet, and starts a new one
 * if connection parameters are correct
 */
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

    /* Clean up the old connection */
    if (thread != NULL || connection != NULL) {
        thread->disconnect();
        thread->exit();
        thread->terminate();
        connection->disconnect();

        thread = NULL;
        connection = NULL;
    }

    /* Create our new connection and start the new game */

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

/**
 * @brief MainWindow::onThreadFinished
 * Close current game
 */
void MainWindow::onThreadFinished()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    thread = NULL;
    connection = NULL;
}

/**
 * @brief MainWindow::onQuit
 * Close the application
 */
void MainWindow::onQuit()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;

    close();
}

/**
 * @brief MainWindow::~MainWindow
 * Destructor for the mainwindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}
