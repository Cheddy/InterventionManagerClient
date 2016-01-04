#ifndef STAFFRANK_H
#define STAFFRANK_H

#include "Model/datastructure.h"

class StaffRank : public DataStructure
{
public:
    StaffRank();
    
    long long getId() const;
    void setId(long long value);
    
    QString getName() const;
    void setName(const QString &value);
    
    int getPermissions() const;
    void setPermissions(int value);
    
private:
    long long id = -1;
    QString name;
    int permissions = 0;
    
public slots:
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
    
};

#endif // STAFFRANK_H
