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

bool Intervention::operator==(Intervention intervention) const
{
    if(intervention.getId() != getId() || intervention.getWard().getId() != getWard().getId() || intervention.getPatient().getId() != getPatient().getId() || intervention.getDateTime() != getDateTime() || intervention.getCompleted() != getCompleted() || intervention.getVerified() != getVerified() || intervention.getImpact().getId() != getImpact().getId() || intervention.getStaff().getId() != getStaff().getId() || intervention.getVerifiedStaff().getId() != getVerifiedStaff().getId() || intervention.getCompletedStaff().getId() != getCompletedStaff().getId() || intervention.getVerifiedDateTime() != getVerifiedDateTime() || intervention.getCompletedDateTime() != getCompletedDateTime()){
        return false;
    }
    
    if(intervention.getDetails().length() == getDetails().length()){
        for(int i = 0; i < intervention.getDetails().length(); i++){
            if(!getDetails().contains(intervention.getDetails()[i])){
                return false;
            }
        }
    }
    if(intervention.getActions().length() == getActions().length()){
        for(int i = 0; i < intervention.getActions().length(); i++){
            if(!getActions().contains(intervention.getActions()[i])){
                return false;
            }
        }
    }
    if(intervention.getOutcomes().length() == getOutcomes().length()){
        for(int i = 0; i < intervention.getOutcomes().length(); i++){
            if(!getOutcomes().contains(intervention.getOutcomes()[i])){
                return false;
            }
        }
    }
    return true;
}

bool Intervention::operator!=(Intervention intervention) const
{
    return !(intervention == *this);    
}

QString Intervention::toString()
{
    QString details;
    if(getDetails().length() > 0){
        details += "<p><span style=\"font-family:arial,helvetica,sans-serif;\">Details:</span></p>\n\n<ol>";
        for(int i = 0; i < getDetails().length(); i++){
            details += getDetails()[i].toString();
        }
        details += "</ol>\n\n";    
    }
    
    QString actions;
    if(getActions().length() > 0){
        actions += "<p><span style=\"font-family:arial,helvetica,sans-serif;\">Actions Taken:</span></p>\n\n<ol>";
        for(int i = 0; i < getActions().length(); i++){
            actions += getActions()[i].toString();
        }
        actions += "</ol>\n\n";        
    }
    
    QString outcomes;
    if(getOutcomes().length() > 0){
        outcomes += "<p><span style=\"font-family:arial,helvetica,sans-serif;\">Outcomes:</span></p>\n\n<ol>";    
        for(int i = 0; i < getOutcomes().length(); i++){
            outcomes += getOutcomes()[i].toString();
        }
        outcomes += "</ol>\n\n";            
    }
    
    QString verifiedBy;
    if(verified){
        verifiedBy = QString("<p>Verified By: %1</p>\n\n<p>Verified On: %2</p>\n\n").arg(verifiedStaff.getDisplayName(), verifiedDateTime.toString("HH:mm dd/MM/yyyy"));
    }
    QString completedBy;
    if(completed){
        completedBy = QString("<p>Completed By: %1</p>\n\n<p>Completed On: %2</p>\n\n").arg(completedStaff.getDisplayName(), completedDateTime.toString("HH:mm dd/MM/yyyy"));
    }
    
    QString string = QString("<!doctype html>\n<html>\n<body>\n<div id=\"header\" style=\"background-color: #0065B7;color: #ffffff;font-family:arial,helvetica,sans-serif;\">\n<h1>Morecambe Bay Hospitals...</h1>\n</div>\n\n<p><span style=\"font-family:arial,helvetica,sans-serif;\">Ward: %1</span></p>\n\n<p><span style=\"font-family:arial,helvetica,sans-serif;\">Date/Time: %2</span></p>\n\n<p><span style=\"font-family:arial,helvetica,sans-serif;\">Staff Name: %3</span></p>\n\n<p><span style=\"font-family:arial,helvetica,sans-serif;\">Patient:</span></p>\n\n<p style=\"margin-left: 40px;\"><span style=\"font-family:arial,helvetica,sans-serif;\">%4</span></p>\n\n%5%6%7%8%9<p><span style=\"font-family:arial,helvetica,sans-serif;\">Impact: %10</span></p>\n</body>\n</html>")
            .arg(ward.getName(), dateTime.toString("HH:mm dd/MM/yyyy"), staff.getDisplayName(), patient.toString(), details, verifiedBy, actions, outcomes).arg(completedBy, impact.getName());    
    return string;
}
