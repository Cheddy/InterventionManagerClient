#ifndef NETUTILS_H
#define NETUTILS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QAuthenticator>


class NetUtils : public QObject
{
    Q_OBJECT
    
public:
    explicit NetUtils(QObject *parent = 0);
    QString get(QString url);
    QNetworkAccessManager *manager;
        
private slots:
    void handleAuth(QNetworkReply* reply,QAuthenticator* auth);
};

#endif // NETUTILS_H
