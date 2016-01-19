#ifndef INTERVENTIONDETAIL_H
#define INTERVENTIONDETAIL_H

#include "Model/datastructure.h"
#include <QMetaType>

class InterventionDetail : public DataStructure
{
public:
    long long getId() const;
    void setId(long long value);
    
    long long getInterventionId() const;
    void setInterventionId(long long value);
    
    QString getDetail() const;
    void setDetail(const QString &value);
    
    QString getDescription() const;
    void setDescription(const QString &value);
    
private:
    long long id = -1;
    long long interventionId = 0;
    QString detail;
    QString description;
    
public slots:
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
};
Q_DECLARE_METATYPE(InterventionDetail)


#endif // INTERVENTIONDETAIL_H
