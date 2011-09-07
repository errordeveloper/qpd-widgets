#define HELLO "qpd version 0.1: we are connected.;\n"
#define CLOSE "qpd version 0.1: see you in a bit!;\n"

#include <QtGui>
#include <QtNetwork/QTcpSocket>

#include <iostream>

#include "qpd_basic.h"
#include "ui_qpd_basic.h"

qpd_basic::qpd_basic(QWidget *parent)
    : QWidget(parent) //, ui(new Ui::qpd_basic)
{
    //ui->setupUi(this);

    pd_host = new QLineEdit("localhost");

    pd_port= new QSpinBox(parent);
    pd_port->setRange(1, 65535);
    pd_port->setValue(2020);
    //maybe TODO, split string: // pd_port->setPrefix(":");

        _put_col = new QLabel(tr(":"));
        _put_col->setBuddy(pd_port);

    connectButton = new QPushButton(tr("bang!"));
    connectButton->setDefault(true);
    connectButton->setEnabled(true);
    //maybe TODO, set finger cursor: // connectButton->setCursor();


        _connectionCheckBox = new QCheckBox(this);
        _connectionCheckBox->setEnabled(false);
        _connectionCheckBox->setTristate(false);

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(connectButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(_connectionCheckBox, QDialogButtonBox::ActionRole);

    qpd_Sock = new QTcpSocket(this);


connect(pd_host, SIGNAL(textChanged(const QString &)),
            this, SLOT(disableConnectButton()));
connect(pd_port, SIGNAL(valueChanged(const QString &)), // mayb it should be 'const int &' ??
            this, SLOT(disableConnectButton()));
connect(connectButton, SIGNAL(clicked()),
            this, SLOT(qpd_socket()));

connect(qpd_Sock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
connect(qpd_Sock, SIGNAL(connected()), this, SLOT(connectionControlsDisable()));

connect(_connectionCheckBox, SIGNAL(clicked()), this, SLOT(qpd_close()));

connect(qpd_Sock, SIGNAL(connected()), this, SLOT(qpd_hello()));
connect(qpd_Sock, SIGNAL(disconnected()), this, SLOT(connectionControlsEnable()));


        QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(pd_host, 0, 0);
    mainLayout->addWidget(_put_col, 0, 1);
    mainLayout->addWidget(pd_port, 0, 2);

    mainLayout->addWidget(buttonBox, 0, 3);
    setLayout(mainLayout);
    //setWindowTitle(tr("Pure Data Qt TCP Connect"));
    connectButton->setFocus();

}


void qpd_basic::disableConnectButton()
{
    connectButton->setEnabled(!pd_host->text().isEmpty()
                                 && !pd_port->text().isEmpty());
    return;
}

void qpd_basic::connectionControlsDisable()
{

    if(!_connectionCheckBox->isChecked())
        _connectionCheckBox->setChecked(true);

    pd_host->setEnabled(false);
    pd_port->setEnabled(false);

    connectButton->setText("bong.");
    connectButton->setEnabled(false);

        _connectionCheckBox->setEnabled(true);

    return;
}

void qpd_basic::connectionControlsEnable()
{
    if(_connectionCheckBox->isChecked())
       _connectionCheckBox->setChecked(false);
       _connectionCheckBox->setEnabled(false);

    pd_host->setEnabled(true);
    pd_port->setEnabled(true);

    connectButton->setEnabled(true);
    connectButton->setText("bang!");

    return;
}


void qpd_basic::displayError(QAbstractSocket::SocketError _err_sock)
{
     // QMessageBox::information(this, tr("socketError"), tr("socketError"));

    connectButton->setText("shit!");
    std::cout << _err_sock;
    // wait(8);
    connectionControlsEnable();

     return;

 }

void qpd_basic::qpd_socket(void)
{
    connectButton->setEnabled(false);
    qpd_Sock->connectToHost(pd_host->text(),
                            pd_port->value());

    return;

}

void qpd_basic::qpd_hello()
{

    /* TEST
    QString str = "hello";
    str.append(";\n");

    qpd_Sock->write(str.toAscii()); //suppose we don't need pointers here :)
    */

    #ifdef HELLO
    qpd_Sock->write(HELLO);
    #else
    qpd_Sock->write("hello;\n");
    #endif
    qpd_Sock->flush();

    return;

}

void qpd_basic::qpd_write(QString _qpd_m)
{

   _qpd_m.append(";\n");

   qpd_Sock->write(_qpd_m.toAscii());

   return;
}

void qpd_basic::qpd_close()
{

#ifdef CLOSE
qpd_Sock->write(CLOSE);
#endif

    qpd_Sock->flush();
    qpd_Sock->close();  // qpd_Sock->disconnectFromHost();
    			// suppose that's the same, slower
/**********************
 *
 * in fact ..we could a lot of vvariouse checking-about
 * with the QSocketAbstractSocket class, but it could actually
 * slow things down and make it too clumsy or whatever! so, WHATEVER ;)
 *
 **********************/

    return;
}

qpd_basic::~qpd_basic()
{
    // delete ui;
}
