#ifndef SELFEDITFORM_H
#define SELFEDITFORM_H
#include <QLineEdit>
#include "Forms/abstractform.h"


class SelfEditForm : public AbstractForm
{
public:
    SelfEditForm();
    QLineEdit *usernameField, *surnameField, *othernamesField, *passwordField;
    
public slots:
    void save();  
};

#endif // SELFEDITFORM_H
