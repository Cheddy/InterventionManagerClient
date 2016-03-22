#include "netutils.h"
#include <QNetworkRequest>
#include <QEventLoop>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QMessageBox>

NetUtils::NetUtils(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::sslErrors, this, &NetUtils::onSSLError);
}

QString NetUtils::get(QString url)
{
    QNetworkRequest req = QNetworkRequest(QUrl(QString(MainWindow::serverAddress + ":" + QString::number(MainWindow::serverPort) + "/" + url)));
    
    QString concatenated = MainWindow::user.getUsername() + ":" + MainWindow::user.getPasswordHash();
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    req.setRawHeader("Authorization", headerData.toLocal8Bit());
    
    QNetworkReply *response = manager->get(req);
    
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    
    
    int code = response->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt();
    if(code == 401){
        QMessageBox::warning(QApplication::activeWindow(), "Error!", "Error Code: " + QString::number(code) + "\nAuthentication Problem!\nSession Will Terminate");                
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        std::exit(0);
    }
    return response->readAll(); 
}

int NetUtils::post(QString url, DataStructure *structure)
{
    QNetworkRequest req = QNetworkRequest(QUrl(QString(MainWindow::serverAddress + ":" + QString::number(MainWindow::serverPort) + "/" + url)));
    
    QString concatenated = MainWindow::user.getUsername() + ":" + MainWindow::user.getPasswordHash();
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    req.setRawHeader("authorization", headerData.toLocal8Bit());
    req.setRawHeader("content-type", "application/x-www-form-urlencoded");
    QByteArray params;
    QJsonObject obj;
    structure->write(obj);
    QJsonDocument doc(obj);    
    params.append("data=" + doc.toJson());

    QNetworkReply *response = manager->post(req, params);
    
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    
    int code = response->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt();
    if(code == 401){
        QMessageBox::warning(QApplication::activeWindow(), "Error!", "Error Code: " + QString::number(code) + "\nAuthentication Problem!\nSession Will Terminate");        
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        std::exit(0);
    }
    return code; 
}

void NetUtils::onSSLError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    if(!MainWindow::ignoreSSLError){
        for(int i = 0; i < errors.length(); i++){
            if(errors[i].errorString() == "The certificate is self-signed, and untrusted"){
                int code = QMessageBox::question(NULL,"SSL Support", (QSslSocket::supportsSsl() == 1 ? "SSL supported, however, the certificate received is self-signed\nContinue?" :"SSL unsupported and the certificate received is self-signed\nContinue?"));            
                if(QMessageBox::Yes != code){
                    reply->finished();               
                }else{
                    MainWindow::ignoreSSLError = true;
                }
            }    
        }
    }
    if(MainWindow::ignoreSSLError){
        reply->ignoreSslErrors(errors);
    }
}

