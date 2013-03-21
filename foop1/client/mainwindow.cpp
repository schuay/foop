#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QsLog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(onQuit()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(onNewGame()));
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
