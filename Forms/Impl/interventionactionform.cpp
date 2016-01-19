#include "interventionactionform.h"
#include <QLabel>
#include "Model/Impl/interventionaction.h"

InterventionActionForm::InterventionActionForm(QListWidgetItem *item) : 
    AbstractForm(item)
{
    InterventionAction action = this->item->data(Qt::UserRole).value<InterventionAction>();
    
    descriptionField = new QLineEdit(action.getDescription());
    
    detailField = new QPlainTextEdit(action.getDetail());
    
    dateTimeField = new QDateTimeEdit();
    dateTimeField->setDateTime(action.getDateTime());
    
    ui->formLayout->addRow(new QLabel("Description"), descriptionField);
    ui->formLayout->addRow(new QLabel("Date/Time"), dateTimeField);
    ui->formLayout->addRow(new QLabel("Detail"), detailField);    
    descriptionField->setFocus();
    
    setWindowTitle("Intervention Action Form");    
}

void InterventionActionForm::save(){
    QVariant var = item->data(Qt::UserRole);   
    InterventionAction action = var.value<InterventionAction>();
    action.setDescription(descriptionField->text());
    action.setDetail(detailField->toPlainText());
    action.setDateTime(dateTimeField->dateTime());
    var.setValue(action);
    item->setData(Qt::UserRole, var);
    item->setText(action.getDescription());
}


