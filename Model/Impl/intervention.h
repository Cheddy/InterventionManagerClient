#ifndef INTERVENTION_H
#define INTERVENTION_H

#include "Model/datastructure.h"
#include "Model/Impl/patient.h"
#include "Model/Impl/ward.h"
#include "Model/Impl/interventionaction.h"
#include "Model/Impl/interventiondetail.h"
#include "Model/Impl/interventionoutcome.h"
#include "Model/Impl/staff.h"
#include "Model/Impl/impact.h"
#include <QMetaType>
#include <QDateTime>
#include <QList>

class Intervention : public DataStructure
{
public:
    Intervention();
    
    long long getId() const;
    void setId(long long value);
    
    bool getVerified() const;
    void setVerified(bool value);
    
    bool getCompleted() const;
    void setCompleted(bool value);
    
    Patient getPatient() const;
    void setPatient(const Patient &value);
    
    Ward getWard() const;
    void setWard(const Ward &value);
    
    Impact getImpact() const;
    void setImpact(const Impact &value);
    
    QList<InterventionDetail> getDetails() const;
    void setDetails(const QList<InterventionDetail> &value);
    
    QList<InterventionAction> getActions() const;
    void setActions(const QList<InterventionAction> &value);
    
    QList<InterventionOutcome> getOutcomes() const;
    void setOutcomes(const QList<InterventionOutcome> &value);
    
    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &value);
    
    QDateTime getVerifiedDateTime() const;
    void setVerifiedDateTime(const QDateTime &value);
    
    QDateTime getCompletedDateTime() const;
    void setCompletedDateTime(const QDateTime &value);
    
    Staff getStaff() const;
    void setStaff(const Staff &value);
    
    Staff getVerifiedStaff() const;
    void setVerifiedStaff(const Staff &value);
    
    Staff getCompletedStaff() const;
    void setCompletedStaff(const Staff &value);
    
    QString getDetailsList();
    
    QString getActionsList();
    
    QString getOutcomesList();
    
private:
    long long id = -1;
    bool verified = false, completed = false;
    Patient patient;
    Ward ward;
    Impact impact;
    QList<InterventionDetail> details;
    QList<InterventionAction> actions;
    QList<InterventionOutcome> outcomes;    
    QDateTime dateTime, verifiedDateTime, completedDateTime;
    Staff staff, verifiedStaff, completedStaff;    
    
public slots:
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
};
Q_DECLARE_METATYPE(Intervention)


#endif // INTERVENTION_H
