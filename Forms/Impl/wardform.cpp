#include "wardform.h"
#include <QLabel>
#include <QPushButton>
#include "Model/Impl/ward.h"

WardForm::WardForm(QListWidgetItem *item) : 
    AbstractForm(item)
{
    Ward ward = this->item->data(Qt::UserRole).value<Ward>();
    nameField = new QLineEdit(ward.getName());
    hospitalField = new HospitalComboBox();
    connect(hospitalField, &HospitalComboBox::countChanged, this, &WardForm::onHospitalCountChanged);
    hospitalField->on_refreshButton_clicked();    
    hospitalField->setHospital(ward.getHospital());
    ui->formLayout->addRow(new QLabel("Name"), nameField);
    ui->formLayout->addRow(new QLabel("Hospital"), hospitalField);    
    nameField->setFocus();
    
    setWindowTitle("Ward Form");
}

void WardForm::save(){
    QVariant var = item->data(Qt::UserRole);   
    Ward ward = var.value<Ward>();
    ward.setName(nameField->text());
    ward.setHospital(hospitalField->getHospital());
    var.setValue(ward);
    item->setData(Qt::UserRole, var);
    item->setText(ward.getName());
}

void WardForm::onHospitalCountChanged(int newCount)
{
    if(newCount < 1){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }else{
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);        
    }
    
}
