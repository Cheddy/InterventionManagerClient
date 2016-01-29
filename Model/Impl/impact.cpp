#include "impact.h"

long long Impact::getId() const
{
    return id;
}

void Impact::setId(long long value)
{
    id = value;
}

QString Impact::getName() const
{
    return name;
}

void Impact::setName(const QString &value)
{
    name = value;
}

bool Impact::operator==(Impact impact) const
{
    return impact.getId() == getId() && impact.getName() == getName();    
}

bool Impact::operator!=(Impact impact) const
{
    return !(impact == *this);
}

void Impact::read(const QJsonObject &json)
{
    name = json["name"].toString();
    id = (long long) json["id"].toDouble();
}

void Impact::write(QJsonObject &json)
{
    json["name"] = name;
    json["id"] = id;
}

QString Impact::toString()
{
    return "Name: " + name;    
}
