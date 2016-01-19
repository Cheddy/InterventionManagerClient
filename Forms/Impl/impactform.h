#ifndef IMPACTFORM_H
#define IMPACTFORM_H
#include <QLineEdit>
#include "Forms/abstractform.h"

class ImpactForm : public AbstractForm
{
public:
    ImpactForm(QListWidgetItem *item);
    QLineEdit *nameField;
    
public slots:
    void save();    
};

#endif // IMPACTFORM_H
