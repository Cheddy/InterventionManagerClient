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
    label = new QLabel();
    ui->serverAddressLineEdit->setText(MainWindow::serverAddress);
    ui->serverPortSpinBox->setValue(MainWindow::serverPort);
    ui->serverAddressLabel->hide();
    ui->serverAddressLineEdit->hide();
    ui->serverPortLabel->hide();
    ui->serverPortSpinBox->hide();
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
        LoginStatus status = attemptLogin();
        if(status == LoginStatus::SUCCESS){
            accept();            
        }else if (status == LoginStatus::FAILURE){
            ui->passwordField->clear();
            label->setText("Incorrect username or password");
            if(ui->formLayout->rowCount() != 3){
                ui->formLayout->addWidget(label);     
            }
        }else{
            ui->passwordField->clear();
            label->setText("Error connecting to server");            
            if(ui->formLayout->rowCount() != 3){
                ui->formLayout->addWidget(label);     
            }
        }
        break;
    }
}

LoginDialog::LoginStatus LoginDialog::attemptLogin()
{
    QNetworkRequest req = QNetworkRequest(QUrl(MainWindow::serverAddress + ":" + QString::number(MainWindow::serverPort) + "/login"));
    QString concatenated = ui->usernameField->text() + ":" + QString::fromUtf8(QCryptographicHash::hash(ui->passwordField->text().toUtf8(), QCryptographicHash::Sha256).toHex());
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    req.setRawHeader("Authorization", headerData.toLocal8Bit());
    
    QNetworkAccessManager manager(this);
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &LoginDialog::onSSLError);
    QNetworkReply *response = manager.get(req);

    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    
    int code = response->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt();
    if(code == 401){
        return LoginStatus::FAILURE;
    }
    if(code == 0){
        return LoginStatus::SERVER_ERROR;
    }
    QJsonDocument loadDoc(QJsonDocument::fromJson(response->readAll()));
    if(loadDoc.isObject()){
        MainWindow::user.read(loadDoc.object());
        if(MainWindow::user.getId() != -1){
            MainWindow::user.setPasswordHash(QString::fromUtf8(QCryptographicHash::hash(ui->passwordField->text().toUtf8(), QCryptographicHash::Sha256).toHex()));
            return LoginStatus::SUCCESS;
        }
    }
    return LoginStatus::FAILURE;    
}


void LoginDialog::on_LoginDialog_rejected()
{
    std::exit(0);    
}

void LoginDialog::onSSLError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    reply->ignoreSslErrors(errors);
}

void LoginDialog::on_showMoreButton_clicked()
{
    if(ui->showMoreButton->text() == "Show More"){
        ui->serverAddressLabel->show();
        ui->serverAddressLineEdit->show();
        ui->serverPortLabel->show();
        ui->serverPortSpinBox->show();  
        ui->showMoreButton->setText("Show Less");
    }else{
        ui->serverAddressLabel->hide();
        ui->serverAddressLineEdit->hide();
        ui->serverPortLabel->hide();
        ui->serverPortSpinBox->hide();   
        ui->showMoreButton->setText("Show More");  
    }
}

void LoginDialog::on_serverAddressLineEdit_textChanged(const QString &text)
{
    MainWindow::serverAddress = text;
}

void LoginDialog::on_serverPortSpinBox_valueChanged(int port)
{
    MainWindow::serverPort = port;
}
