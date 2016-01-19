#ifndef HOSPITALFORM_H
#define HOSPITALFORM_H
#include <QLineEdit>
#include "Forms/abstractform.h"

class HospitalForm : public AbstractForm
{
public:
    HospitalForm(QListWidgetItem *item);
    QLineEdit *nameField;
public slots:
    void save();    
    
};

#endif // HOSPITALFORM_H
