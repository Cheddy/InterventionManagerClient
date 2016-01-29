#ifndef IMPACT_H
#define IMPACT_H

#include "Model/datastructure.h"
#include <QMetaType>

class Impact : public DataStructure
{
    
public:
    long long getId() const;
    void setId(long long value);
    
    QString getName() const;
    void setName(const QString &value);
    
    bool operator==(Impact impact) const;
    bool operator!=(Impact impact) const;

private:
    long long id = -1;
    QString name;
    
public slots:
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
    QString toString();    
    
};
Q_DECLARE_METATYPE(Impact)


#endif // IMPACT_H
