#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QLabel>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    bool attemptLogin();
    QLabel *label;
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
        
    void on_LoginDialog_rejected();
    
private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
