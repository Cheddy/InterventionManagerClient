#include "staffrankform.h"
#include <QLabel>
#include "Model/Impl/staffrank.h"
#include "mainwindow.h"
#include <QDebug>

StaffRankForm::StaffRankForm(QListWidgetItem *item) : 
    AbstractForm(item)
{
    StaffRank rank = this->item->data(Qt::UserRole).value<StaffRank>();
    nameField = new QLineEdit(rank.getName());
    
    newHospitalBox = new QCheckBox();
    newHospitalBox->setChecked((rank.getPermissions() & MainWindow::NEW_HOSPITAL_PERMISSION) != 0);
    editHospitalBox = new QCheckBox();
    editHospitalBox->setChecked((rank.getPermissions() & MainWindow::EDIT_HOSPITAL_PERMISSION) != 0);
    deleteHospitalBox = new QCheckBox();
    deleteHospitalBox->setChecked((rank.getPermissions() & MainWindow::DELETE_HOSPITAL_PERMISSION) != 0);
    
    newImpactBox = new QCheckBox();
    newImpactBox->setChecked((rank.getPermissions() & MainWindow::NEW_IMPACT_PERMISSION) != 0);
    editImpactBox = new QCheckBox();
    editImpactBox->setChecked((rank.getPermissions() & MainWindow::EDIT_IMPACT_PERMISSION) != 0);
    deleteImpactBox = new QCheckBox();
    deleteImpactBox->setChecked((rank.getPermissions() & MainWindow::DELETE_IMPACT_PERMISSION) != 0);
    
    newPatientBox = new QCheckBox();
    newPatientBox->setChecked((rank.getPermissions() & MainWindow::NEW_PATIENT_PERMISSION) != 0);
    editPatientBox = new QCheckBox();
    editPatientBox->setChecked((rank.getPermissions() & MainWindow::EDIT_PATIENT_PERMISSION) != 0);
    deletePatientBox = new QCheckBox();
    deletePatientBox->setChecked((rank.getPermissions() & MainWindow::DELETE_PATIENT_PERMISSION) != 0);
    
    newStaffBox = new QCheckBox();
    newStaffBox->setChecked((rank.getPermissions() & MainWindow::NEW_STAFF_PERMISSION) != 0);
    editStaffBox = new QCheckBox();
    editStaffBox->setChecked((rank.getPermissions() & MainWindow::EDIT_STAFF_PERMISSION) != 0);
    deleteStaffBox = new QCheckBox();
    deleteStaffBox->setChecked((rank.getPermissions() & MainWindow::DELETE_STAFF_PERMISSION) != 0);
    
    newStaffRankBox = new QCheckBox();
    newStaffRankBox->setChecked((rank.getPermissions() & MainWindow::NEW_STAFF_RANK_PERMISSION) != 0);
    editStaffRankBox = new QCheckBox();
    editStaffRankBox->setChecked((rank.getPermissions() & MainWindow::EDIT_STAFF_RANK_PERMISSION) != 0);
    deleteStaffRankBox = new QCheckBox();
    deleteStaffRankBox->setChecked((rank.getPermissions() & MainWindow::DELETE_STAFF_RANK_PERMISSION) != 0);
    
    newWardBox = new QCheckBox();
    newWardBox->setChecked((rank.getPermissions() & MainWindow::NEW_WARD_PERMISSION) != 0);
    editWardBox = new QCheckBox();
    editWardBox->setChecked((rank.getPermissions() & MainWindow::EDIT_WARD_PERMISSION) != 0);
    deleteWardBox = new QCheckBox();
    deleteWardBox->setChecked((rank.getPermissions() & MainWindow::DELETE_WARD_PERMISSION) != 0);    
    
    newInterventionBox = new QCheckBox();
    newInterventionBox->setChecked((rank.getPermissions() & MainWindow::NEW_INTERVENTION_PERMISSION) != 0);
    editInterventionBox = new QCheckBox();
    editInterventionBox->setChecked((rank.getPermissions() & MainWindow::EDIT_INTERVENTION_PERMISSION) != 0);
    deleteInterventionBox = new QCheckBox();
    deleteInterventionBox->setChecked((rank.getPermissions() & MainWindow::DELETE_INTERVENTION_PERMISSION) != 0);        
    
    newInterventionDetailBox = new QCheckBox();
    newInterventionDetailBox->setChecked((rank.getPermissions() & MainWindow::NEW_INTERVENTION_DETAIL_PERMISSION) != 0);
    editInterventionDetailBox = new QCheckBox();
    editInterventionDetailBox->setChecked((rank.getPermissions() & MainWindow::EDIT_INTERVENTION_DETAIL_PERMISSION) != 0);
    deleteInterventionDetailBox = new QCheckBox();
    deleteInterventionDetailBox->setChecked((rank.getPermissions() & MainWindow::DELETE_INTERVENTION_DETAIL_PERMISSION) != 0);   
    
    newInterventionActionBox = new QCheckBox();
    newInterventionActionBox->setChecked((rank.getPermissions() & MainWindow::NEW_INTERVENTION_ACTION_PERMISSION) != 0);
    editInterventionActionBox = new QCheckBox();
    editInterventionActionBox->setChecked((rank.getPermissions() & MainWindow::EDIT_INTERVENTION_ACTION_PERMISSION) != 0);
    deleteInterventionActionBox = new QCheckBox();
    deleteInterventionActionBox->setChecked((rank.getPermissions() & MainWindow::DELETE_INTERVENTION_ACTION_PERMISSION) != 0);   
    
    newInterventionOutcomeBox = new QCheckBox();
    newInterventionOutcomeBox->setChecked((rank.getPermissions() & MainWindow::NEW_INTERVENTION_OUTCOME_PERMISSION) != 0);
    editInterventionOutcomeBox = new QCheckBox();
    editInterventionOutcomeBox->setChecked((rank.getPermissions() & MainWindow::EDIT_INTERVENTION_OUTCOME_PERMISSION) != 0);
    deleteInterventionOutcomeBox = new QCheckBox();
    deleteInterventionOutcomeBox->setChecked((rank.getPermissions() & MainWindow::DELETE_INTERVENTION_OUTCOME_PERMISSION) != 0);   
    
    viewLogsBox = new QCheckBox();
    viewLogsBox->setChecked((rank.getPermissions() & MainWindow::VIEW_LOGS_PERMISSION) != 0);
    clearLogsBox = new QCheckBox();
    clearLogsBox->setChecked((rank.getPermissions() & MainWindow::CLEAR_LOGS_PERMISSION) != 0);       
    
    ui->formLayout->addRow(new QLabel("Name"), nameField);
    ui->formLayout->addRow(new QLabel("Permissions"));        
    ui->formLayout->addRow(new QLabel("Create Hospitals"), newHospitalBox);    
    ui->formLayout->addRow(new QLabel("Edit Hospitals"), editHospitalBox);    
    ui->formLayout->addRow(new QLabel("Delete Hospitals"), deleteHospitalBox);        
    ui->formLayout->addRow(new QLabel("Create Impacts"), newImpactBox);    
    ui->formLayout->addRow(new QLabel("Edit Impacts"), editImpactBox);    
    ui->formLayout->addRow(new QLabel("Delete Impacts"), deleteImpactBox);   
    ui->formLayout->addRow(new QLabel("Create Patients"), newPatientBox);    
    ui->formLayout->addRow(new QLabel("Edit Patients"), editPatientBox);    
    ui->formLayout->addRow(new QLabel("Delete Patients"), deletePatientBox);        
    ui->formLayout->addRow(new QLabel("Create Staff"), newStaffBox);    
    ui->formLayout->addRow(new QLabel("Edit Staff"), editStaffBox);    
    ui->formLayout->addRow(new QLabel("Delete Staff"), deleteStaffBox);        
    ui->formLayout->addRow(new QLabel("Create Staff Ranks"), newStaffRankBox);    
    ui->formLayout->addRow(new QLabel("Edit Staff Ranks"), editStaffRankBox);    
    ui->formLayout->addRow(new QLabel("Delete Staff Ranks"), deleteStaffRankBox);        
    ui->formLayout->addRow(new QLabel("Create Wards"), newWardBox);    
    ui->formLayout->addRow(new QLabel("Edit Wards"), editWardBox);    
    ui->formLayout->addRow(new QLabel("Delete Wards"), deleteWardBox);        
    ui->formLayout->addRow(new QLabel("Create Interventions"), newInterventionBox);    
    ui->formLayout->addRow(new QLabel("Edit Interventions"), editInterventionBox);    
    ui->formLayout->addRow(new QLabel("Delete Interventions"), deleteInterventionBox);        
    ui->formLayout->addRow(new QLabel("Create Intervention Details"), newInterventionDetailBox);    
    ui->formLayout->addRow(new QLabel("Edit Intervention Details"), editInterventionDetailBox);    
    ui->formLayout->addRow(new QLabel("Delete Intervention Details"), deleteInterventionDetailBox);        
    ui->formLayout->addRow(new QLabel("Create Intervention Actions"), newInterventionActionBox);    
    ui->formLayout->addRow(new QLabel("Edit Intervention Actions"), editInterventionActionBox);    
    ui->formLayout->addRow(new QLabel("Delete Intervention Actions"), deleteInterventionActionBox);        
    ui->formLayout->addRow(new QLabel("Create Intervention Outcomes"), newInterventionOutcomeBox);    
    ui->formLayout->addRow(new QLabel("Edit Intervention Outcomes"), editInterventionOutcomeBox);    
    ui->formLayout->addRow(new QLabel("Delete Intervention Outcomes"), deleteInterventionOutcomeBox);        
    ui->formLayout->addRow(new QLabel("View Logs"), viewLogsBox);    
    ui->formLayout->addRow(new QLabel("Clear Logs"), clearLogsBox);        
   
    connect(deleteInterventionBox, &QCheckBox::toggled, this, &StaffRankForm::stateChanged);
    
    nameField->setFocus();    
    
    setWindowTitle("Staff Rank Form");
}

void StaffRankForm::save(){
    QVariant var = item->data(Qt::UserRole);   
    StaffRank rank = var.value<StaffRank>();
    rank.setName(nameField->text().trimmed());
    rank.setPermissions(0LL);
    rank.permissions |= (newHospitalBox->isChecked()? MainWindow::NEW_HOSPITAL_PERMISSION : 0);
    rank.permissions |= (editHospitalBox->isChecked()? MainWindow::EDIT_HOSPITAL_PERMISSION : 0);
    rank.permissions |= (deleteHospitalBox->isChecked()? MainWindow::DELETE_HOSPITAL_PERMISSION : 0);
    rank.permissions |= (newImpactBox->isChecked()? MainWindow::NEW_IMPACT_PERMISSION : 0);
    rank.permissions |= (editImpactBox->isChecked()? MainWindow::EDIT_IMPACT_PERMISSION : 0);
    rank.permissions |= (deleteImpactBox->isChecked()? MainWindow::DELETE_IMPACT_PERMISSION : 0);
    rank.permissions |= (newPatientBox->isChecked()? MainWindow::NEW_PATIENT_PERMISSION : 0);
    rank.permissions |= (editPatientBox->isChecked()? MainWindow::EDIT_PATIENT_PERMISSION : 0);
    rank.permissions |= (deletePatientBox->isChecked()? MainWindow::DELETE_PATIENT_PERMISSION : 0);
    rank.permissions |= (newStaffBox->isChecked()? MainWindow::NEW_STAFF_PERMISSION : 0);
    rank.permissions |= (editStaffBox->isChecked()? MainWindow::EDIT_STAFF_PERMISSION : 0);
    rank.permissions |= (deleteStaffBox->isChecked()? MainWindow::DELETE_STAFF_PERMISSION : 0);
    rank.permissions |= (newStaffRankBox->isChecked()? MainWindow::NEW_STAFF_RANK_PERMISSION : 0);
    rank.permissions |= (editStaffRankBox->isChecked()? MainWindow::EDIT_STAFF_RANK_PERMISSION : 0);
    rank.permissions |= (deleteStaffRankBox->isChecked()? MainWindow::DELETE_STAFF_RANK_PERMISSION : 0);
    rank.permissions |= (newWardBox->isChecked()? MainWindow::NEW_WARD_PERMISSION : 0);
    rank.permissions |= (editWardBox->isChecked()? MainWindow::EDIT_WARD_PERMISSION : 0);
    rank.permissions |= (deleteWardBox->isChecked()? MainWindow::DELETE_WARD_PERMISSION : 0);
    rank.permissions |= (newInterventionBox->isChecked()? MainWindow::NEW_INTERVENTION_PERMISSION : 0);
    rank.permissions |= (editInterventionBox->isChecked()? MainWindow::EDIT_INTERVENTION_PERMISSION : 0);
    rank.permissions |= (deleteInterventionBox->isChecked()? MainWindow::DELETE_INTERVENTION_PERMISSION : 0);
    rank.permissions |= (newInterventionDetailBox->isChecked()? MainWindow::NEW_INTERVENTION_DETAIL_PERMISSION : 0);
    rank.permissions |= (editInterventionDetailBox->isChecked()? MainWindow::EDIT_INTERVENTION_DETAIL_PERMISSION : 0);
    rank.permissions |= (deleteInterventionDetailBox->isChecked()? MainWindow::DELETE_INTERVENTION_DETAIL_PERMISSION : 0);
    rank.permissions |= (newInterventionActionBox->isChecked()? MainWindow::NEW_INTERVENTION_ACTION_PERMISSION : 0);
    rank.permissions |= (editInterventionActionBox->isChecked()? MainWindow::EDIT_INTERVENTION_ACTION_PERMISSION : 0);
    rank.permissions |= (deleteInterventionActionBox->isChecked()? MainWindow::DELETE_INTERVENTION_ACTION_PERMISSION : 0);
    rank.permissions |= (newInterventionOutcomeBox->isChecked()? MainWindow::NEW_INTERVENTION_OUTCOME_PERMISSION : 0);
    rank.permissions |= (editInterventionOutcomeBox->isChecked()? MainWindow::EDIT_INTERVENTION_OUTCOME_PERMISSION : 0);
    rank.permissions |= (deleteInterventionOutcomeBox->isChecked()? MainWindow::DELETE_INTERVENTION_OUTCOME_PERMISSION : 0);
    rank.permissions |= (viewLogsBox->isChecked()? MainWindow::VIEW_LOGS_PERMISSION : 0);
    rank.permissions |= (clearLogsBox->isChecked()? MainWindow::CLEAR_LOGS_PERMISSION : 0);
    var.setValue(rank);
    item->setData(Qt::UserRole, var);
    item->setText(rank.getName());
}

void StaffRankForm::stateChanged()
{
    if(deleteInterventionBox->isChecked()){
        deleteInterventionDetailBox->setChecked(true);        
        deleteInterventionActionBox->setChecked(true);
        deleteInterventionOutcomeBox->setChecked(true);        
    }
}
