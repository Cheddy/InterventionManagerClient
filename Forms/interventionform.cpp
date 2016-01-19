#include "interventionform.h"
#include "ui_interventionform.h"
#include "Model/Impl/intervention.h"
#include <QLabel>
#include "mainwindow.h"

InterventionForm::InterventionForm(QList<QTableWidgetItem *> list) :
    QDialog(),
    ui(new Ui::InterventionForm)
{
    ui->setupUi(this);
    this->list = list;
    
    QTableWidgetItem *item = list[0];
    QVariant var = item->data(Qt::UserRole);   
    Intervention intervention = var.value<Intervention>();
    
    patientField = new PatientComboBox();
    patientField->on_refreshButton_clicked();    
    patientField->setPatient(intervention.getPatient());
    
    wardField = new WardComboBox();
    wardField->on_refreshButton_clicked();    
    wardField->setWard(intervention.getWard());
    
    dateTimeField = new QDateTimeEdit();
    dateTimeField->setDateTime(intervention.getDateTime());
    
    detailManagerField = new InterventionDetailManager();
    detailManagerField->add(intervention.getDetails());
    
    verifiedField = new QCheckBox();
    verifiedField->setChecked(intervention.getVerified());
    
    actionManagerField = new InterventionActionManager();
    actionManagerField->add(intervention.getActions());
    
    outcomeManagerField = new InterventionOutcomeManager();
    outcomeManagerField->add(intervention.getOutcomes());
    
    impactField = new ImpactComboBox();
    impactField->on_refreshButton_clicked();
    impactField->setImpact(intervention.getImpact());
    
    completedField = new QCheckBox();
    completedField->setChecked(intervention.getCompleted());
    
    ui->formLayout->addRow(new QLabel("Patient"), patientField);
    ui->formLayout->addRow(new QLabel("Ward"), wardField);        
    ui->formLayout->addRow(new QLabel("Date/Time"), dateTimeField);        
    ui->formLayout->addRow(new QLabel("Details"), detailManagerField);
    ui->formLayout->addRow(new QLabel("Verified"), verifiedField);
    ui->formLayout->addRow(new QLabel("Actions Taken"), actionManagerField);
    ui->formLayout->addRow(new QLabel("Outcomes"), outcomeManagerField);
    ui->formLayout->addRow(new QLabel("Impact"), impactField);
    ui->formLayout->addRow(new QLabel("Completed"), completedField);
    
    
}

InterventionForm::~InterventionForm()
{
    delete ui;
}

void InterventionForm::on_buttonBox_accepted()
{
    QTableWidgetItem *item = list[0];
    QVariant var = item->data(Qt::UserRole);   
    Intervention intervention = var.value<Intervention>();
    if(intervention.getId() == -1){
        intervention.setStaff(MainWindow::user);
    }
    intervention.setPatient(patientField->getPatient());
    intervention.setWard(wardField->getWard());
    intervention.setDateTime(dateTimeField->dateTime());
    intervention.setDetails(detailManagerField->get());
    if(verifiedField->isChecked() != intervention.getVerified()){
        if(verifiedField->isChecked()){
            intervention.setVerifiedDateTime(QDateTime::currentDateTime());
            intervention.setVerifiedStaff(MainWindow::user);
        }else{
            intervention.setVerifiedStaff(Staff());
            intervention.setVerifiedDateTime(QDateTime());            
        }
    }
    intervention.setVerified(verifiedField->isChecked());
    intervention.setActions(actionManagerField->get());
    intervention.setOutcomes(outcomeManagerField->get());
    intervention.setImpact(impactField->getImpact());
    if(completedField->isChecked() != intervention.getCompleted()){
        if(completedField->isChecked()){
            intervention.setCompletedStaff(MainWindow::user);
            intervention.setCompletedDateTime(QDateTime::currentDateTime());
        }else{
            intervention.setCompletedStaff(Staff());
            intervention.setCompletedDateTime(QDateTime());            
        }
    }
    intervention.setCompleted(completedField->isChecked());
    
    var.setValue(intervention);
    item->setData(Qt::UserRole, var);
    
      
    item->setText(intervention.getStaff().getDisplayName());
    list[1]->setText(intervention.getDateTime().toString("yyyy/MM/dd HH:mm:ss"));
    list[2]->setText(intervention.getVerifiedStaff().getDisplayName());
    list[3]->setText(intervention.getVerifiedDateTime().toString("yyyy/MM/dd HH:mm:ss"));
    list[4]->setText(intervention.getWard().getName());    
    list[5]->setText(intervention.getPatient().getDisplayName());  
    list[6]->setText(intervention.getDetailsList());  
    list[7]->setText(intervention.getActionsList());  
    list[8]->setText(intervention.getOutcomesList());  
    list[9]->setText(intervention.getCompletedStaff().getDisplayName());
    list[10]->setText(intervention.getCompletedDateTime().toString("yyyy/MM/dd HH:mm:ss"));
    list[11]->setText(intervention.getImpact().getName());    
}
