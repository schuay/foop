#include <QtGui>
#include "connectionDialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent, QString *strHost, QString *strPort, int *iMode)
    : QDialog(parent)
{
    //Set Pointers
    this->strHost = strHost;
    this->strPort = strPort;
    this->iMode = iMode;

    //Host-Input fields
    labelHost = new QLabel("&Host:");
    lineEditHost = new QLineEdit;
    lineEditHost->setInputMask("000.000.000.000");
    lineEditHost->setText(*(this->strHost));
    labelHost->setBuddy(lineEditHost);

    //Port-Input fields
    labelPort = new QLabel("&Port:");
    lineEditPort = new QLineEdit;
    lineEditPort->setInputMask("00000"); //a number with a maximum length of 5 digits
    lineEditPort->setText(*(this->strPort));
    labelPort->setBuddy(lineEditPort);

    //Find-Button
    tryButton = new QPushButton(tr("&Try"));

    connect(tryButton, SIGNAL(clicked()), this, SLOT(findConnection()));

    //Layout-Style
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(labelHost);
    topLeftLayout->addWidget(lineEditHost);

    QHBoxLayout *bottomLeftLayout = new QHBoxLayout;
    bottomLeftLayout->addWidget(labelPort);
    bottomLeftLayout->addWidget(lineEditPort);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addLayout(bottomLeftLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addStretch();
    rightLayout->addWidget(tryButton);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    //Dialog-Settings
    setModal(true);
    setWindowTitle("Connect 2 Game");
    setFixedHeight(sizeHint().height());
}

void ConnectionDialog::findConnection()
{
    *(this->strHost) = lineEditHost->text();
    *(this->strPort) = lineEditPort->text();
    *(this->iMode) = 1;
    this->close();
}
