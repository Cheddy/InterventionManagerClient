#include "interventionaction.h"

long long InterventionAction::getId() const
{
    return id;
}

void InterventionAction::setId(long long value)
{
    id = value;
}

long long InterventionAction::getInterventionId() const
{
    return interventionId;
}

void InterventionAction::setInterventionId(long long value)
{
    interventionId = value;
}

QDateTime InterventionAction::getDateTime() const
{
    return dateTime;
}

void InterventionAction::setDateTime(const QDateTime &value)
{
    dateTime = value;
}

QString InterventionAction::getDetail() const
{
    return detail;
}

void InterventionAction::setDetail(const QString &value)
{
    detail = value;
}

QString InterventionAction::getDescription() const
{
    return description;
}

void InterventionAction::setDescription(const QString &value)
{
    description = value;
}

void InterventionAction::read(const QJsonObject &json)
{
    description = json["description"].toString();
    detail = json["detail"].toString();
    id = (long long) json["id"].toDouble();
    interventionId = (long long) json["interventionId"].toDouble();
    dateTime = QDateTime::fromString(json["dateTime"].toString(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")),"yyyy-MM-dd HH:mm:ss");    
}

void InterventionAction::write(QJsonObject &json)
{
    json["description"] = description;
    json["detail"] = detail;    
    json["id"] = id;
    json["interventionId"] = interventionId;
    json["dateTime"] = dateTime.toString("yyyy-MM-dd HH:mm:ss");        
}
