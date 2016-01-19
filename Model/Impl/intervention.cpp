#include "intervention.h"
#include <QJsonArray>

Intervention::Intervention()
{
    dateTime = QDateTime::currentDateTime();
}

long long Intervention::getId() const
{
    return id;
}

void Intervention::setId(long long value)
{
    id = value;
}

bool Intervention::getVerified() const
{
    return verified;
}

void Intervention::setVerified(bool value)
{
    verified = value;
}

bool Intervention::getCompleted() const
{
    return completed;
}

void Intervention::setCompleted(bool value)
{
    completed = value;
}

Patient Intervention::getPatient() const
{
    return patient;
}

void Intervention::setPatient(const Patient &value)
{
    patient = value;
}

Ward Intervention::getWard() const
{
    return ward;
}

void Intervention::setWard(const Ward &value)
{
    ward = value;
}

Impact Intervention::getImpact() const
{
    return impact;
}

void Intervention::setImpact(const Impact &value)
{
    impact = value;
}

QList<InterventionDetail> Intervention::getDetails() const
{
    return details;
}

void Intervention::setDetails(const QList<InterventionDetail> &value)
{
    details = value;
}

QList<InterventionAction> Intervention::getActions() const
{
    return actions;
}

void Intervention::setActions(const QList<InterventionAction> &value)
{
    actions = value;
}

QList<InterventionOutcome> Intervention::getOutcomes() const
{
    return outcomes;
}

void Intervention::setOutcomes(const QList<InterventionOutcome> &value)
{
    outcomes = value;
}

QDateTime Intervention::getDateTime() const
{
    return dateTime;
}

void Intervention::setDateTime(const QDateTime &value)
{
    dateTime = value;
}

QDateTime Intervention::getVerifiedDateTime() const
{
    return verifiedDateTime;
}

void Intervention::setVerifiedDateTime(const QDateTime &value)
{
    verifiedDateTime = value;
}

QDateTime Intervention::getCompletedDateTime() const
{
    return completedDateTime;
}

void Intervention::setCompletedDateTime(const QDateTime &value)
{
    completedDateTime = value;
}

Staff Intervention::getStaff() const
{
    return staff;
}

void Intervention::setStaff(const Staff &value)
{
    staff = value;
}

Staff Intervention::getVerifiedStaff() const
{
    return verifiedStaff;
}

void Intervention::setVerifiedStaff(const Staff &value)
{
    verifiedStaff = value;
}

Staff Intervention::getCompletedStaff() const
{
    return completedStaff;
}

void Intervention::setCompletedStaff(const Staff &value)
{
    completedStaff = value;
}

void Intervention::read(const QJsonObject &json)
{
    id = (long long) json["id"].toDouble();    
    if(json.contains("patient")){
        patient.read(json["patient"].toObject());
    }
    if(json.contains("ward")){
        ward.read(json["ward"].toObject());
    }
    if(json.contains("staff")){
        staff.read(json["staff"].toObject());
    }
    if(json.contains("verifiedStaff")){
        verifiedStaff.read(json["verifiedStaff"].toObject());
    }
    if(json.contains("completedStaff")){
        completedStaff.read(json["completedStaff"].toObject());
    }
    if(json.contains("impact")){
        impact.read(json["impact"].toObject());
    }
    if(json.contains("details") && json["details"].isArray()){
        QJsonArray array = json["details"].toArray();
        for(int i = 0; i < array.size(); i++){
            InterventionDetail detail;
            detail.read(array[i].toObject());
            details << detail;
        }
    }
    
    if(json.contains("actions") && json["actions"].isArray()){
        QJsonArray array = json["actions"].toArray();
        for(int i = 0; i < array.size(); i++){
            InterventionAction action;
            action.read(array[i].toObject());
            actions << action;
        }
    }
    
    if(json.contains("outcomes") && json["outcomes"].isArray()){
        QJsonArray array = json["outcomes"].toArray();
        for(int i = 0; i < array.size(); i++){
            InterventionOutcome outcome;
            outcome.read(array[i].toObject());
            outcomes << outcome;
        }
    }
    
    verified = json["verified"].toBool();
    completed = json["completed"].toBool();
    
    dateTime = QDateTime::fromString(json["dateTime"].toString(QDateTime().toString("yyyy-MM-dd HH:mm:ss")),"yyyy-MM-dd HH:mm:ss");
    verifiedDateTime = QDateTime::fromString(json["verifiedDateTime"].toString(QDateTime().toString("yyyy-MM-dd HH:mm:ss")),"yyyy-MM-dd HH:mm:ss");
    completedDateTime = QDateTime::fromString(json["completedDateTime"].toString(QDateTime().toString("yyyy-MM-dd HH:mm:ss")),"yyyy-MM-dd HH:mm:ss");
    
}

void Intervention::write(QJsonObject &json)
{
    json["id"] = id;
    json["dateTime"] = dateTime.toString("yyyy-MM-dd HH:mm:ss");
    if(!verifiedDateTime.isNull()){
        json["verifiedDateTime"] = verifiedDateTime.toString("yyyy-MM-dd HH:mm:ss");    
    }
    if(!completedDateTime.isNull()){    
        json["completedDateTime"] = completedDateTime.toString("yyyy-MM-dd HH:mm:ss");   
    }
    json["verified"] = verified;
    json["completed"] = completed;
    
    if(patient.getId() != -1){
        QJsonObject obj;        
        patient.write(obj);
        json["patient"] = obj;
    }
    
    if(ward.getId() != -1){
        QJsonObject obj;        
        ward.write(obj);
        json["ward"] = obj;
    }
    
    if(impact.getId() != -1){
        QJsonObject obj;        
        impact.write(obj);
        json["impact"] = obj;
    }
    
    if(staff.getId() != -1){
        QJsonObject obj;        
        staff.write(obj);
        json["staff"] = obj;
    }
    
    if(verifiedStaff.getId() != -1){
        QJsonObject obj;        
        verifiedStaff.write(obj);
        json["verifiedStaff"] = obj;
    }
    
    if(completedStaff.getId() != -1){
        QJsonObject obj;        
        completedStaff.write(obj);
        json["completedStaff"] = obj;
    }
    
    QJsonArray arrayDetails;
    for(int i = 0; i < details.size(); i++){
        QJsonObject obj;        
        details[i].write(obj);
        arrayDetails << obj;        
    }
    json["details"] = arrayDetails;
    
    QJsonArray arrayActions;
    for(int i = 0; i < actions.size(); i++){
        QJsonObject obj;        
        actions[i].write(obj);
        arrayActions << obj;        
    }
    json["actions"] = arrayActions;
    
    QJsonArray arrayOutcomes;
    for(int i = 0; i < outcomes.size(); i++){
        QJsonObject obj;        
        outcomes[i].write(obj);
        arrayOutcomes << obj;        
    }
    json["outcomes"] = arrayOutcomes;
    
}

QString Intervention::getActionsList()
{
    QString actionsList;
    if(getActions().length() > 0){
        actionsList += "[";    
        for(int i = 0; i < getActions().length(); i++){
            if(i > 0){
                actionsList += ", ";
            }
            actionsList += getActions()[i].getDescription();
        }
        actionsList += "]";
    }
    return actionsList;
}

QString Intervention::getDetailsList()
{
    QString detailsList;
    if(getDetails().length() > 0){
        detailsList += "[";    
        for(int i = 0; i < getDetails().length(); i++){
            if(i > 0){
                detailsList += ", ";
            }
            detailsList += getDetails()[i].getDescription();
        }
        detailsList += "]";
    }
    return detailsList;
}

QString Intervention::getOutcomesList()
{
    QString outcomesList;
    if(getOutcomes().length() > 0){
        outcomesList += "[";    
        for(int i = 0; i < getOutcomes().length(); i++){
            if(i > 0){
                outcomesList += ", ";
            }
            outcomesList += getOutcomes()[i].getDescription();
        }
        outcomesList += "]";
    }
    return outcomesList;
}
