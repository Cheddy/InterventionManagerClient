#include "interventionoutcome.h"

long long InterventionOutcome::getId() const
{
    return id;
}

void InterventionOutcome::setId(long long value)
{
    id = value;
}

long long InterventionOutcome::getInterventionId() const
{
    return interventionId;
}

void InterventionOutcome::setInterventionId(long long value)
{
    interventionId = value;
}

QDateTime InterventionOutcome::getDateTime() const
{
    return dateTime;
}

void InterventionOutcome::setDateTime(const QDateTime &value)
{
    dateTime = value;
}

QString InterventionOutcome::getDetail() const
{
    return detail;
}

void InterventionOutcome::setDetail(const QString &value)
{
    detail = value;
}

QString InterventionOutcome::getDescription() const
{
    return description;
}

void InterventionOutcome::setDescription(const QString &value)
{
    description = value;
}

bool InterventionOutcome::operator==(InterventionOutcome interventionOutcome) const
{
    return interventionOutcome.getId() == getId() && interventionOutcome.getInterventionId() == getInterventionId() && interventionOutcome.getDescription() == getDescription() && interventionOutcome.getDateTime() == getDateTime() && interventionOutcome.getDetail() == getDetail();    
}

bool InterventionOutcome::operator!=(InterventionOutcome interventionOutcome) const
{
    return !(interventionOutcome == *this);
}

void InterventionOutcome::read(const QJsonObject &json)
{
    description = json["description"].toString();
    detail = json["detail"].toString();
    id = (long long) json["id"].toDouble();
    interventionId = (long long) json["interventionId"].toDouble();
    dateTime = QDateTime::fromString(json["dateTime"].toString(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")),"yyyy-MM-dd HH:mm:ss");    
}

void InterventionOutcome::write(QJsonObject &json)
{
    json["description"] = description;
    json["detail"] = detail;    
    json["id"] = id;
    json["interventionId"] = interventionId;
    json["dateTime"] = dateTime.toString("yyyy-MM-dd HH:mm:ss");        
}

QString InterventionOutcome::toString()
{
    QString string;
    string += "\n\t<li><span style=\"font-family:arial,helvetica,sans-serif;\">Description: " + description + "<br>";
    string += "Date/Time: " + dateTime.toString("HH:mm dd/MM/yyyy") + "<br>";        
    string += "Detail: " + detail.replace("\n"," || ") + "</span></li>";
    return string;
}
