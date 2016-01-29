#include "patientmanager.h"
#include "Model/Impl/patient.h"
#include "Network/netutils.h"
#include "Forms/Impl/patientform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QList>
#include <QMessageBox>
#include "mainwindow.h"

PatientManager::PatientManager()
{
    onPermissionsChanged();
    refresh();
}

void PatientManager::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_PATIENT_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
    if((permissions & MainWindow::EDIT_PATIENT_PERMISSION) == 0){
        ui->editButton->setVisible(false);
    }else{
        ui->editButton->setVisible(true);
    }
    if((permissions & MainWindow::DELETE_PATIENT_PERMISSION) == 0){
        ui->deleteButton->setVisible(false);
    }else{
        ui->deleteButton->setVisible(true);
    }
}


void PatientManager::add()
{
    Patient patient;
    patient.setSurname("New Member");
    patient.setOthernames("New Member");    
    
    QVariant var;
    var.setValue(patient);
    QListWidgetItem *item = new QListWidgetItem(patient.getDisplayName());
    item->setData(Qt::UserRole, var);
    
    PatientForm *form = new PatientForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ui->listWidget->addItem(item);
        patient = var.value<Patient>();                
        onAdd(&patient);        
    }else{
        delete item;
    }
}

void PatientManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        QVariant var = item->data(Qt::UserRole);   
        Patient original = var.value<Patient>();                
        
        PatientForm *form = new PatientForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            var = item->data(Qt::UserRole);   
            Patient patient = var.value<Patient>();  
            if(original != patient){
                onEdit(&patient);
            }
        }
        
    }
}

void PatientManager::deleteFunction()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            Patient patient = var.value<Patient>();        
            onDelete(&patient);
        }
    }
}

void PatientManager::refresh()
{
    ui->listWidget->clear();
    NetUtils net;
    QString html = net.get("patient/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Patient patient;
        patient.read(array[i].toObject());
        QVariant var;
        var.setValue(patient);
        QListWidgetItem *item = new QListWidgetItem(patient.getDisplayName());
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

void PatientManager::onAdd(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("patient/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void PatientManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("patient/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
}

void PatientManager::onDelete(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("patient/delete", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
    }
    refresh();        
}
