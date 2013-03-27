#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

#include "QsLog.h"
#include "serverconnection.h"

#define HOST ("localhost")
#define PORT (16384)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(onQuit()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(onNewGame()));

    view = new View(this);
    scene = view->createScene();

    setCentralWidget(view);

    /* Start the server connection thread. This will be moved to
     * the 'New Game...' menu a little later. We will also need to
     * terminate and clean up left over old connections. */
    QThread *thread = new QThread();

    ServerConnection *connection = new ServerConnection(HOST, PORT);
    connection->moveToThread(thread);

    qRegisterMetaType<Snake::Direction>("Snake::Direction");
    connect(scene, SIGNAL(directionChange(Snake::Direction)),
            connection, SLOT(onDirectionChange(Snake::Direction)));

    connect(thread, SIGNAL(started()), connection, SLOT(run()));
    connect(connection, SIGNAL(finished()), thread, SLOT(quit()));
    connect(connection, SIGNAL(finished()), connection, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

void MainWindow::onNewGame()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;
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
