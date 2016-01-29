#include "hospitalform.h"
#include <QLabel>
#include "Model/Impl/hospital.h"

HospitalForm::HospitalForm(QListWidgetItem *item) : 
    AbstractForm(item)
{
    nameField = new QLineEdit(this->item->data(Qt::UserRole).value<Hospital>().getName());
    
    ui->formLayout->addRow(new QLabel("Name"), nameField);
    nameField->setFocus();  
    
    setWindowTitle("Hospital Form");
}

void HospitalForm::save(){
    QVariant var = item->data(Qt::UserRole);   
    Hospital hospital = var.value<Hospital>();
    hospital.setName(nameField->text().trimmed());
    var.setValue(hospital);
    item->setData(Qt::UserRole, var);
    item->setText(hospital.getName());
}
