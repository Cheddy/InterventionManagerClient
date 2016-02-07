#ifndef STAFFFORM_H
#define STAFFFORM_H
#include <QLineEdit>
#include "Components/staffrankcombobox.h"
#include "Forms/abstractform.h"

class StaffForm : public AbstractForm
{
public:
    StaffForm(QListWidgetItem *item);
    QLineEdit *usernameField, *surnameField, *othernamesField, *passwordField;
    StaffRankComboBox *rankField;
    
public slots:
    void save();  
    void onStaffRankCountChanged(int newCount);
};

#endif // STAFFFORM_H
