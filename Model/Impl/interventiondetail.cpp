#include "interventiondetail.h"


long long InterventionDetail::getId() const
{
    return id;
}

void InterventionDetail::setId(long long value)
{
    id = value;
}

long long InterventionDetail::getInterventionId() const
{
    return interventionId;
}

void InterventionDetail::setInterventionId(long long value)
{
    interventionId = value;
}

QString InterventionDetail::getDetail() const
{
    return detail;
}

void InterventionDetail::setDetail(const QString &value)
{
    detail = value;
}

QString InterventionDetail::getDescription() const
{
    return description;
}

void InterventionDetail::setDescription(const QString &value)
{
    description = value;
}

bool InterventionDetail::operator==(InterventionDetail interventionDetail) const
{
    return interventionDetail.getId() == getId() && interventionDetail.getInterventionId() == getInterventionId() && interventionDetail.getDescription() == getDescription() && interventionDetail.getDetail() == getDetail();        
}

bool InterventionDetail::operator!=(InterventionDetail interventionDetail) const
{
    return !(interventionDetail == *this);
}

void InterventionDetail::read(const QJsonObject &json)
{
    description = json["description"].toString();
    detail = json["detail"].toString();
    id = (long long) json["id"].toDouble();
    interventionId = (long long) json["interventionId"].toDouble();
}

void InterventionDetail::write(QJsonObject &json)
{
    json["description"] = description;
    json["detail"] = detail;    
    json["id"] = id;
    json["interventionId"] = interventionId;
}

QString InterventionDetail::toString()
{
    QString string;
    string += "\n\t<li><span style=\"font-family:arial,helvetica,sans-serif;\">Description: " + description + "<br>";
    string += "Detail: " + detail.replace("\n"," || ") + "</span></li>";
    return string;
}
