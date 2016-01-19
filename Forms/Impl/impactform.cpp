#include "impactform.h"
#include <QLabel>
#include "Model/Impl/impact.h"

ImpactForm::ImpactForm(QListWidgetItem *item) : 
    AbstractForm(item)
{
    nameField = new QLineEdit(this->item->data(Qt::UserRole).value<Impact>().getName());
    
    ui->formLayout->addRow(new QLabel("Name"), nameField);
    nameField->setFocus();  
    
    setWindowTitle("Impact Form");    
}

void ImpactForm::save(){
    QVariant var = item->data(Qt::UserRole);   
    Impact impact = var.value<Impact>();
    impact.setName(nameField->text());
    var.setValue(impact);
    item->setData(Qt::UserRole, var);
    item->setText(impact.getName());
}
