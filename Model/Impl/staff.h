#ifndef STAFF_H
#define STAFF_H

#include "Model/datastructure.h"
#include "Model/Impl/staffrank.h"
#include <QMetaType>

class Staff : public DataStructure
{
    
public:
    long long getId() const;
    void setId(long long value);
    
    QString getUsername() const;
    void setUsername(const QString &value);
    
    QString getSurname() const;
    void setSurname(const QString &value);
    
    QString getOthernames() const;
    void setOthernames(const QString &value);
    
    QString getPasswordHash() const;
    void setPasswordHash(const QString &value);
    
    StaffRank getRank() const;
    void setRank(const StaffRank &value);
    
    QString getDisplayName() const;    
    
private:
    long long id = -1;
    QString username;
    QString surname;
    QString othernames;
    QString passwordHash;
    StaffRank rank;
    
public slots:
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
    
};
Q_DECLARE_METATYPE(Staff)


#endif // STAFF_H
