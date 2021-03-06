#include "ward.h"

long long Ward::getId() const
{
    return id;
}

void Ward::setId(long long value)
{
    id = value;
}

QString Ward::getName() const
{
    return name;
}

void Ward::setName(const QString &value)
{
    name = value;
}

Hospital Ward::getHospital() const
{
    return hospital;
}

void Ward::setHospital(const Hospital &value)
{
    hospital = value;
}

bool Ward::operator==(Ward ward) const
{
    return ward.getId() == getId() && ward.getName() == getName() && ward.getHospital().getId() == getHospital().getId();            
}

bool Ward::operator!=(Ward ward) const
{
    return !(ward == *this);                
}

void Ward::read(const QJsonObject &json)
{
    name = json["name"].toString();
    id = (long long) json["id"].toDouble();
    if(json.contains("hospital")){
        hospital.read(json["hospital"].toObject());
    }
}

void Ward::write(QJsonObject &json)
{
    json["name"] = name;
    json["id"] = id;
    if(hospital.getId() != -1){
        QJsonObject hospital;        
        this->hospital.write(hospital);
        json["hospital"] = hospital;
    }
}

QString Ward::toString()
{
    QString string;
    string += "Name: " + name + "<br>";
    string += "Hospital: " + hospital.getName();
    return string;
}
