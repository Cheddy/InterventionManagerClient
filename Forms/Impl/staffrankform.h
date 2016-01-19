#ifndef STAFFRANKFORM_H
#define STAFFRANKFORM_H
#include <QLineEdit>
#include <QDoubleSpinBox>
#include "Forms/abstractform.h"

class StaffRankForm : public AbstractForm
{
public:
    StaffRankForm(QListWidgetItem *item);
    QLineEdit *nameField;
    QDoubleSpinBox *permissionField;
    
public slots:
    void save();    
};

#endif // STAFFRANKFORM_H
