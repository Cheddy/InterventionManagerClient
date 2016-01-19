#include "logindialog.h"
#include "ui_logindialog.h"
#include <QJsonDocument>
#include "mainwindow.h"
#include <QDialogButtonBox>
#include "Model/Impl/staff.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    disconnect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    label = new QLabel("Incorrect username or password");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    int standardButton = ui->buttonBox->standardButton(button);
    switch(standardButton) {
    case QDialogButtonBox::Ok: 
        if(attemptLogin()){
            accept();            
        }else{
            ui->passwordField->clear();
            if(ui->formLayout->rowCount() != 3){
                ui->formLayout->addWidget(label);     
            }
        }
        break;
    }
}

bool LoginDialog::attemptLogin()
{
    QNetworkRequest req = QNetworkRequest(QUrl("http://localhost:8080/login"));
    QString concatenated = ui->usernameField->text() + ":" + QString::fromUtf8(QCryptographicHash::hash(ui->passwordField->text().toUtf8(), QCryptographicHash::Sha256).toHex());
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    req.setRawHeader("Authorization", headerData.toLocal8Bit());
    
    QNetworkAccessManager manager(this);
    QNetworkReply *response = manager.get(req);
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    
    int code = response->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt();
    if(code == 401){
        return false;
    }
    QJsonDocument loadDoc(QJsonDocument::fromJson(response->readAll()));
    if(loadDoc.isObject()){
        MainWindow::user.read(loadDoc.object());
        if(MainWindow::user.getId() != -1){
            MainWindow::user.setPasswordHash(QString::fromUtf8(QCryptographicHash::hash(ui->passwordField->text().toUtf8(), QCryptographicHash::Sha256).toHex()));
            return true;
        }
    }
    return false;    
}


void LoginDialog::on_LoginDialog_rejected()
{
    std::exit(0);    
}
