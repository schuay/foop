#include "mainwindow.h"
#include "ui_mainwindow.h"

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

}

void MainWindow::onQuit()
{
    close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
