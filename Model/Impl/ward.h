#ifndef WARD_H
#define WARD_H

#include "Model/datastructure.h"
#include "Model/Impl/hospital.h"
#include <QMetaType>

class Ward : public DataStructure
{

public:
    long long getId() const;
    void setId(long long value);
    
    QString getName() const;
    void setName(const QString &value);
    
    Hospital getHospital() const;
    void setHospital(const Hospital &value);

    bool operator==(Ward ward) const;    
    bool operator!=(Ward ward) const;                    
    
private:
    long long id = -1;
    QString name;
    Hospital hospital;
    
public slots:
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
    QString toString();            
    
};
Q_DECLARE_METATYPE(Ward)

#endif // WARD_H
