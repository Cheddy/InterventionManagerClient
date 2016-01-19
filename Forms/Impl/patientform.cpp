#include "patientform.h"
#include <QLabel>
#include "Model/Impl/patient.h"

PatientForm::PatientForm(QListWidgetItem *item) : 
    AbstractForm(item)
{
    Patient patient = this->item->data(Qt::UserRole).value<Patient>();
    
    surnameField = new QLineEdit(patient.getSurname());
    othernamesField = new QLineEdit(patient.getOthernames());
    rtxField = new QDoubleSpinBox();
    rtxField->setMinimum(0);
    rtxField->setMaximum(9007199254740992);
    rtxField->setDecimals(0);
    rtxField->setValue(patient.getRtx());
    dobField = new QDateEdit();
    dobField->setDate(patient.getDob());
    
    ui->formLayout->addRow(new QLabel("Surname"), surnameField);
    ui->formLayout->addRow(new QLabel("Other Names"), othernamesField);
    ui->formLayout->addRow(new QLabel("RTX"), rtxField);    
    ui->formLayout->addRow(new QLabel("DOB"), dobField);        
    surnameField->setFocus();   
    
    setWindowTitle("Patient Form");
}

void PatientForm::save(){
    QVariant var = item->data(Qt::UserRole);   
    Patient patient = var.value<Patient>();
    patient.setSurname(surnameField->text());
    patient.setOthernames(othernamesField->text());
    patient.setRtx((long long) rtxField->value());
    patient.setDob(dobField->date());
    var.setValue(patient);
    item->setData(Qt::UserRole, var);
    item->setText(patient.getDisplayName());
}


