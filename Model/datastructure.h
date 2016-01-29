#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QJsonObject>

class DataStructure
{
public:
    virtual void read(const QJsonObject &json) = 0;
    virtual void write(QJsonObject &json) = 0;
    virtual QString toString() = 0;
};


#endif // DATASTRUCTURE_H
