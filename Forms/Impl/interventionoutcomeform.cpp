#include "interventionoutcomeform.h"
#include <QLabel>
#include "Model/Impl/interventionoutcome.h"

InterventionOutcomeForm::InterventionOutcomeForm(QListWidgetItem *item) : 
    AbstractForm(item)
{
    InterventionOutcome outcome = this->item->data(Qt::UserRole).value<InterventionOutcome>();
    
    descriptionField = new QLineEdit(outcome.getDescription());
    
    detailField = new QPlainTextEdit(outcome.getDetail());
    
    dateTimeField = new QDateTimeEdit();
    dateTimeField->setDateTime(outcome.getDateTime());
    
    ui->formLayout->addRow(new QLabel("Description"), descriptionField);
    ui->formLayout->addRow(new QLabel("Date/Time"), dateTimeField);
    ui->formLayout->addRow(new QLabel("Detail"), detailField);    
    descriptionField->setFocus();    
    
    setWindowTitle("Intervention Outcome Form");
}

void InterventionOutcomeForm::save(){
    QVariant var = item->data(Qt::UserRole);   
    InterventionOutcome outcome = var.value<InterventionOutcome>();
    outcome.setDescription(descriptionField->text());
    outcome.setDetail(detailField->toPlainText());
    outcome.setDateTime(dateTimeField->dateTime());
    var.setValue(outcome);
    item->setData(Qt::UserRole, var);
    item->setText(outcome.getDescription());
}


