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
