#include "netutils.h"
#include <QNetworkRequest>
#include <QEventLoop>

NetUtils::NetUtils(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    Q_ASSERT(manager);
    connect(manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(handleAuth(QNetworkReply*,QAuthenticator*)));
}

QString NetUtils::get(QString url)
{
    QNetworkRequest req = QNetworkRequest(QUrl(url));
    QNetworkReply *response = manager->get(req);
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    return response->readAll(); 
}

void NetUtils::handleAuth(QNetworkReply* reply,QAuthenticator* auth)
{
   auth->setUser("cheddy");
   auth->setPassword("f990974d8bd704ab073495f7e5e5f67383fea6ea1eab9bb415e210f92a4286");
}
