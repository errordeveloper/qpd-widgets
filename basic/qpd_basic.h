#ifndef QPD_BASIC_H
#define QPD_BASIC_H


#include <QtCore/QObject>
#include <QtGui/QWidget>
#include <QtGui/QDialog>
#include <QtNetwork/QTcpSocket>

#include <QtDesigner/QDesignerExportWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QSpinBox;
class QCheckBox;
class QLineEdit;
class QPushButton;
class QDialogButtonBox;
class QTcpSocket;
QT_END_NAMESPACE


// namespace Ui
// {
//     class qpd_basic;
// }


class QDESIGNER_WIDGET_EXPORT qpd_basic : public QWidget
{
    Q_OBJECT

public:
    qpd_basic(QWidget *parent = 0);
    ~qpd_basic();

public slots:
    void qpd_socket(); // init socket;
    void qpd_hello(); // write msg;
    void qpd_write(QString _qpd_m);

private slots:
    void displayError(QAbstractSocket::SocketError _err_sock);
    void disableConnectButton();
    void connectionControlsDisable();
    void connectionControlsEnable();
    void qpd_close(); // close socket;

private:
    // Ui::qpd_basic *ui;

    QLineEdit *pd_host;
    QSpinBox *pd_port;
    QLabel *_put_col;
    QCheckBox *_connectionCheckBox;
    QPushButton *connectButton;
    QDialogButtonBox *buttonBox;

    QTcpSocket *qpd_Sock;
    quint16 blockSize;
};

#endif // QPD_BASIC_H
