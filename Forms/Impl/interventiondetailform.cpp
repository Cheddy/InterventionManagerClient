#include "interventiondetailform.h"
#include <QLabel>
#include "Model/Impl/interventiondetail.h"

InterventionDetailForm::InterventionDetailForm(QListWidgetItem *item) : 
    AbstractForm(item)
{
    InterventionDetail detail = this->item->data(Qt::UserRole).value<InterventionDetail>();
    
    descriptionField = new QLineEdit(detail.getDescription());
    
    detailField = new QPlainTextEdit(detail.getDetail());
    
    ui->formLayout->addRow(new QLabel("Description"), descriptionField);
    ui->formLayout->addRow(new QLabel("Detail"), detailField);    
    descriptionField->setFocus();    
    
    setWindowTitle("Intervention Detail Form");
}

void InterventionDetailForm::save(){
    QVariant var = item->data(Qt::UserRole);   
    InterventionDetail detail = var.value<InterventionDetail>();
    detail.setDescription(descriptionField->text());
    detail.setDetail(detailField->toPlainText());
    var.setValue(detail);
    item->setData(Qt::UserRole, var);
    item->setText(detail.getDescription());
}

