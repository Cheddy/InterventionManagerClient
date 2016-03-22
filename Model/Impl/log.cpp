#include "log.h"
#include "Model/Impl/hospital.h"
#include "Model/Impl/impact.h"
#include "Model/Impl/patient.h"
#include "Model/Impl/staff.h"
#include "Model/Impl/staffrank.h"
#include "Model/Impl/intervention.h"
#include "Model/Impl/ward.h"


long Log::getOpcode() const
{
    return opcode;
}

void Log::setOpcode(long value)
{
    opcode = value;
}

QString Log::getDescription() const
{
    return description;
}

void Log::setDescription(const QString &value)
{
    description = value;
}

QDateTime Log::getTimestamp() const
{
    return timestamp;
}

void Log::setTimestamp(const QDateTime &value)
{
    timestamp = value;
}

Staff Log::getStaff() const
{
    return staff;
}

void Log::setStaff(const Staff &value)
{
    staff = value;
}

DataStructure* Log::getOldItem()
{
    return oldItem;
}

void Log::setOldItem(DataStructure *value)
{
    oldItem = value;
}

DataStructure* Log::getNewItem()
{
    return newItem;
}

void Log::setNewItem(DataStructure *value)
{
    newItem = value;
}

void Log::read(const QJsonObject &json)
{
    description = json["description"].toString();
    opcode = json["opcode"].toInt();
    timestamp = QDateTime::fromString(json["timestamp"].toString(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")),"yyyy-MM-dd HH:mm:ss");    
    id = (long long) json["id"].toDouble();
    if(json.contains("staff")){
        staff.read(json["staff"].toObject());
    }
    if(json.contains("staff")){
        staff.read(json["staff"].toObject());
    }
    if(opcode != -1){
        int type = opcode % 3;
        int storableType = opcode / 3;
        switch (storableType) {
        case 0:
            if(type < 2){
                newItem = new Hospital();
                newItem->read(json["newItem"].toObject());
            }
            if(type > 0){
                oldItem = new Hospital();
                oldItem->read(json["oldItem"].toObject());
            }
            break;
        case 1:
            if(type < 2){
                newItem = new Impact();
                newItem->read(json["newItem"].toObject());
            }
            if(type > 0){
                oldItem = new Impact();
                oldItem->read(json["oldItem"].toObject());
            }
            break;
        case 2:
            if(type < 2){            
                newItem = new Patient();
                newItem->read(json["newItem"].toObject());
            }
            if(type > 0){
                oldItem = new Patient();
                oldItem->read(json["oldItem"].toObject());
            }
            break;
        case 3:
            if(type < 2){                
                newItem = new Staff();
                newItem->read(json["newItem"].toObject());
            }
            if(type > 0){
                oldItem = new Staff();
                oldItem->read(json["oldItem"].toObject());
            }
            break;
        case 4:
            if(type < 2){                
                newItem = new StaffRank();
                newItem->read(json["newItem"].toObject());
            }
            if(type > 0){
                oldItem = new StaffRank();
                oldItem->read(json["oldItem"].toObject());
            }
            break;
        case 5:
            if(type < 2){                
                newItem = new Ward();
                newItem->read(json["newItem"].toObject());
            }
            if(type > 0){
                oldItem = new Ward();
                oldItem->read(json["oldItem"].toObject());
            }
            break;
        case 6:
            if(type < 2){                
                newItem = new Intervention();
                newItem->read(json["newItem"].toObject());
            }
            if(type > 0){
                oldItem = new Intervention();
                oldItem->read(json["oldItem"].toObject());
            }
            break;
        }
    }
}

void Log::write(QJsonObject &json)
{
    
}

QString Log::toString()
{
    QString string;
    string += "Staff: " + staff.getPrintName() + "<br>";
    string += "Description: " + description + "<br>";
    string += "Date/Time: " + timestamp.toString("HH:mm dd/MM/yyyy") + "<br>";    
    if(opcode != -1){
        int type = opcode % 3;
        if(type < 2){
            string += "<br>New Item:<br>" + newItem->toString() + "<br>";            
        }
        if(type > 0){
            string += "<br>Old Item:<br>" + oldItem->toString();            
        }
    }    
    return string;
}
