#ifndef WARDFORM_H
#define WARDFORM_H
#include <QLineEdit>
#include <QSignalMapper>
#include "Components/hospitalcombobox.h"
#include "Forms/abstractform.h"

class WardForm : public AbstractForm
{
public:
    WardForm(QListWidgetItem *item);
    QLineEdit *nameField;
    HospitalComboBox *hospitalField;
    
public slots:
    void save();  
    void onHospitalCountChanged(int newCount);
};

#endif // WARDFORM_H
