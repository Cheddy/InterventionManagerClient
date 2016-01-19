#ifndef PATIENTFORM_H
#define PATIENTFORM_H
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include "Forms/abstractform.h"

class PatientForm : public AbstractForm
{
public:
    PatientForm(QListWidgetItem *item);
    QLineEdit *surnameField, *othernamesField;
    QDoubleSpinBox *rtxField;
    QDateEdit *dobField;
    
public slots:
    void save();    
};

#endif // PATIENTFORM_H
