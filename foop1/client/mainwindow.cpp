#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QsLog.h"
#include "connectionDialog.h"

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

    //if you want a newgame, the old will be destroyed
    if (thread != 0) {
        thread->disconnect();
        thread->exit();
        thread->terminate();
        connection->disconnect();

        thread = 0;
        connection = 0;
    }

    //exchange parameters with default values
    QString strHost = "127.0.0.1";
    QString strPort = "16384";
    int iMode = -1;

    //Start Connection-Dialog
    ConnectionDialog *conDialog = new ConnectionDialog(this, &strHost, &strPort, &iMode);

    if (conDialog->exec() == QDialog::Accepted) {
        return;
    }

    if (iMode == 1) {
        /* Start the server connection thread. This will be moved to
         * the 'New Game...' menu a little later. We will also need to
         * terminate and clean up left over old connections. */

        thread = new QThread();

        connection = new ServerConnection(strHost, strPort.toInt());
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

        thread->start();
    }
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
