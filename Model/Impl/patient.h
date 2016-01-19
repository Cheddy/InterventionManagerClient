#ifndef PATIENT_H
#define PATIENT_H

#include "Model/datastructure.h"
#include <QMetaType>
#include <QDate>

class Patient : public DataStructure
{
public:
    long long getId() const;
    void setId(long long value);
    
    long long getRtx() const;
    void setRtx(long long value);
    
    QDate getDob() const;
    void setDob(const QDate &value);
    
    QString getSurname() const;
    void setSurname(const QString &value);
    
    QString getOthernames() const;
    void setOthernames(const QString &value);
    
    QString getDisplayName() const;
    
private:
    long long id = -1;
    long long rtx = 0;
    QDate dob;
    QString surname;
    QString othernames;
    
public slots:
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
};
Q_DECLARE_METATYPE(Patient)


#endif // PATIENT_H
