#ifndef STAFFRANK_H
#define STAFFRANK_H

#include "Model/datastructure.h"
#include <QMetaType>

class StaffRank : public DataStructure
{
    
public:
    long long getId() const;
    void setId(long long value);
    
    QString getName() const;
    void setName(const QString &value);
    
    long long getPermissions() const;
    void setPermissions(long long value);
    
private:
    long long id = -1;
    QString name;
    long long permissions = 0;
    
public slots:
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
    
};
Q_DECLARE_METATYPE(StaffRank)

#endif // STAFFRANK_H
