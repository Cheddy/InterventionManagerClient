#ifndef NETUTILS_H
#define NETUTILS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QAuthenticator>
#include <Model/datastructure.h>


class NetUtils : public QObject
{
    Q_OBJECT
    
public:
    explicit NetUtils(QObject *parent = 0);
    QString get(QString url);
    int post(QString url, DataStructure *structure);
    QNetworkAccessManager *manager;
};

#endif // NETUTILS_H
