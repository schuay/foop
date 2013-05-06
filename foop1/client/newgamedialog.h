#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>

namespace Ui
{
class NewGameDialog;
}

/**
 * @brief The NewGameDialog class
 * Provides the dialog for a new game,
 * includes fields for a hostname and
 * the portnumber to connect to the
 * game server
 */
class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameDialog(QWidget *parent = 0);
    ~NewGameDialog();

    QString host() const;
    int port() const;

private:
    Ui::NewGameDialog *ui;
};

#endif // NEWGAMEDIALOG_H
