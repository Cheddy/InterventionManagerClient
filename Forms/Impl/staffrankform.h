#ifndef STAFFRANKFORM_H
#define STAFFRANKFORM_H
#include <QLineEdit>
#include <QSpinBox>
#include "Forms/abstractform.h"

class StaffRankForm : public AbstractForm
{
public:
    StaffRankForm(QListWidgetItem *item);
    QLineEdit *nameField;
    QSpinBox *permissionField;
    
public slots:
    void save();    
};

#endif // STAFFRANKFORM_H
