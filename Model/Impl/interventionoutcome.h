#ifndef INTERVENTIONOUTCOME_H
#define INTERVENTIONOUTCOME_H

#include "Model/datastructure.h"
#include <QMetaType>
#include <QDateTime>

class InterventionOutcome : public DataStructure
{
public:
    long long getId() const;
    void setId(long long value);
    
    long long getInterventionId() const;
    void setInterventionId(long long value);
    
    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &value);
    
    QString getDetail() const;
    void setDetail(const QString &value);
    
    QString getDescription() const;
    void setDescription(const QString &value);
    
    bool operator==(InterventionOutcome interventionOutcome) const;        
    bool operator!=(InterventionOutcome interventionOutcome) const;        
    
private:
    long long id = -1;
    long long interventionId;
    QDateTime dateTime;
    QString detail;
    QString description;
    
public slots:
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
    QString toString();            
};
Q_DECLARE_METATYPE(InterventionOutcome)

#endif // INTERVENTIONOUTCOME_H
