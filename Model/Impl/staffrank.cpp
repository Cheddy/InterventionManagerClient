#include "staffrank.h"

long long StaffRank::getPermissions() const
{
    return permissions;
}

void StaffRank::setPermissions(long long value)
{
    permissions = value;
}

QString StaffRank::getName() const
{
    return name;
}

void StaffRank::setName(const QString &value)
{
    name = value;
}

long long StaffRank::getId() const
{
    return id;
}

void StaffRank::setId(long long value)
{
    id = value;
}

void StaffRank::read(const QJsonObject &json)
{
    name = json["name"].toString();
    id = (long long) json["id"].toDouble();
    permissions = (long long) json["permissions"].toDouble();
}

void StaffRank::write(QJsonObject &json)
{
    json["name"] = name;
    json["id"] = id;
    json["permissions"] = permissions;
}
