#include "newgamedialog.h"
#include "ui_newgamedialog.h"

/**
 * @brief NewGameDialog::NewGameDialog
 * creates the new-game-dialog
 * @param parent Qt-Element above
 */
NewGameDialog::NewGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameDialog)
{
    ui->setupUi(this);
}

NewGameDialog::~NewGameDialog()
{
    delete ui;
}

QString NewGameDialog::host() const
{
    return ui->host->text();
}

int NewGameDialog::port() const
{
    return ui->port->value();
}
