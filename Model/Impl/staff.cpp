#include "staff.h"

QString Staff::getUsername() const
{
    return username;
}

void Staff::setUsername(const QString &value)
{
    username = value;
}

QString Staff::getSurname() const
{
    return surname;
}

void Staff::setSurname(const QString &value)
{
    surname = value;
}

QString Staff::getOthernames() const
{
    return othernames;
}

void Staff::setOthernames(const QString &value)
{
    othernames = value;
}

QString Staff::getPasswordHash() const
{
    return passwordHash;
}

void Staff::setPasswordHash(const QString &value)
{
    passwordHash = value;
}

StaffRank Staff::getRank() const
{
    return rank;
}

void Staff::setRank(const StaffRank &value)
{
    rank = value;
}

QString Staff::getDisplayName() const
{
    return othernames + " " + surname + (!username.isEmpty()? (" [" + username + "]") : "");
}

QString Staff::getPrintName() const
{
    return othernames + " " + surname;
}

bool Staff::operator==(Staff staff) const
{
    return staff.getId() == getId() && staff.getPasswordHash() == getPasswordHash() && staff.getRank().getId() == getRank().getId() && staff.getSurname() == getSurname() && staff.getOthernames() == getOthernames() && staff.getUsername() == getUsername();            
}

bool Staff::operator!=(Staff staff) const
{
    return !(staff == *this);        
}

long long Staff::getId() const
{
    return id;
}

void Staff::setId(long long value)
{
    id = value;
}

void Staff::read(const QJsonObject &json)
{
    username = json["username"].toString();
    surname = json["surname"].toString();
    othernames = json["othernames"].toString();    
    id = (long long) json["id"].toDouble();
    if(json.contains("rank")){
        rank.read(json["rank"].toObject());
    }
}

void Staff::write(QJsonObject &json)
{
    json["surname"] = surname;
    json["othernames"] = othernames;
    json["username"] = username;
    if(!passwordHash.isEmpty()){
        json["passwordHash"] = passwordHash;
    }
    json["id"] = id;
    if(rank.getId() != -1){
        QJsonObject rank;        
        this->rank.write(rank);
        json["rank"] = rank;
    }
}

QString Staff::toString()
{
    QString string;
    string += "Surname: " + surname + "<br>";
    string += "Other Names: " + othernames + "<br>";    
    string += "Username: " + username + "<br>";        
    string += "Position: " + rank.getName();
    return string;
}
