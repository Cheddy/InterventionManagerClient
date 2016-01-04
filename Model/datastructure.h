#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QObject>
#include <QJsonObject>

class DataStructure : public QObject
{
    Q_OBJECT
public:
    explicit DataStructure(QObject *parent = 0);
    
signals:
    
public slots:
    virtual void read(const QJsonObject &json) = 0;
    virtual void write(QJsonObject &json) = 0;
    
};

#endif // DATASTRUCTURE_H
