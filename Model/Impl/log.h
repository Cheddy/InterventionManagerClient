#ifndef LOG_H
#define LOG_H

#include "Model/datastructure.h"
#include "Model/Impl/staff.h"
#include <QMetaType>
#include <QDateTime>

class Log : public DataStructure
{
public:
    long long getId() const;
    void setId(long long value);
    
    long getOpcode() const;
    void setOpcode(long value);
    
    QString getDescription() const;
    void setDescription(const QString &value);
    
    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime &value);
    
    Staff getStaff() const;
    void setStaff(const Staff &value);
    
    DataStructure* getOldItem();
    void setOldItem(DataStructure *value);
    
    DataStructure* getNewItem();
    void setNewItem(DataStructure *value);
    
private:
    long long id = -1LL;
    long opcode;
    QString description;
    DataStructure *oldItem = NULL, *newItem = NULL;
    QDateTime timestamp;
    Staff staff;
    
public slots:
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
    QString toString();  
    
};
Q_DECLARE_METATYPE(Log)

#endif // LOG_H
