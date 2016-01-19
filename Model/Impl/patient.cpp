#include "patient.h"

long long Patient::getId() const
{
    return id;
}

void Patient::setId(long long value)
{
    id = value;
}

long long Patient::getRtx() const
{
    return rtx;
}

void Patient::setRtx(long long value)
{
    rtx = value;
}

QDate Patient::getDob() const
{
    return dob;
}

void Patient::setDob(const QDate &value)
{
    dob = value;
}

QString Patient::getSurname() const
{
    return surname;
}

void Patient::setSurname(const QString &value)
{
    surname = value;
}

QString Patient::getOthernames() const
{
    return othernames;
}

QString Patient::getDisplayName() const
{
    return QString::number(rtx) + " : " + othernames + " " + surname;
}


void Patient::setOthernames(const QString &value)
{
    othernames = value;
}


void Patient::read(const QJsonObject &json)
{
    othernames = json["othernames"].toString();
    surname = json["surname"].toString();
    id = (long long) json["id"].toDouble();
    rtx = (long long) json["rtx"].toDouble();
    dob = QDate::fromString(json["dob"].toString("1900-01-01"),"yyyy-MM-dd");
}

void Patient::write(QJsonObject &json)
{
    json["othernames"] = othernames;
    json["surname"] = surname;    
    json["id"] = id;
    json["rtx"] = rtx;
    json["dob"] = dob.toString("yyyy-MM-dd");    
}
