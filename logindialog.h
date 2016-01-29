#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QLabel>
#include <QSslError>
#include <QNetworkReply>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    enum LoginStatus {SUCCESS, FAILURE, SERVER_ERROR};    
    LoginStatus attemptLogin();
    QLabel *label;
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_LoginDialog_rejected();
    void onSSLError(QNetworkReply *reply, const QList<QSslError> &errors);
    void on_showMoreButton_clicked();
    
    void on_serverAddressLineEdit_textChanged(const QString &text);
    
    void on_serverPortSpinBox_valueChanged(int port);
    
private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
