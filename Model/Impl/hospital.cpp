#include "hospital.h"

long long Hospital::getId() const
{
    return id;
}

void Hospital::setId(long long value)
{
    id = value;
}

QString Hospital::getName() const
{
    return name;
}

void Hospital::setName(const QString &value)
{
    name = value;
}

void Hospital::read(const QJsonObject &json)
{
    name = json["name"].toString();
    id = (long long) json["id"].toDouble();
}

void Hospital::write(QJsonObject &json)
{
    json["name"] = name;
    json["id"] = id;
}

QString Hospital::toString()
{
    return "Name: " + name;
}

bool Hospital::operator==(Hospital hospital) const
{
    return hospital.getId() == getId() && hospital.getName() == getName();
}

bool Hospital::operator!=(Hospital hospital) const
{
    return !(hospital == *this);
}
