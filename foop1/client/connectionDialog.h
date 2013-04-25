#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    ConnectionDialog(QWidget *parent = 0, QString *strHost = 0, QString *strPort = 0, int *iMode = 0);

private slots:
    void findConnection();

private:
    QString *strHost;
    QString *strPort;
    int *iMode;

    QLabel *labelHost;
    QLabel *labelPort;
    QLineEdit *lineEditHost;
    QLineEdit *lineEditPort;
    QPushButton *tryButton;
};

#endif // CONNECTIONDIALOG_H
