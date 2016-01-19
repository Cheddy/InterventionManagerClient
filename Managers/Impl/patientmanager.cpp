#include "patientmanager.h"
#include "Model/Impl/patient.h"
#include "Network/netutils.h"
#include "Forms/Impl/patientform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QList>
#include <QMessageBox>

PatientManager::PatientManager()
{
    refresh();
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
        
        PatientForm *form = new PatientForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            QVariant var = item->data(Qt::UserRole);   
            Patient patient = var.value<Patient>();        
            onEdit(&patient);
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
    QString html = net.get("http://localhost:8080/patient/all");
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
    int response = net.post("http://localhost:8080/patient/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void PatientManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/patient/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
}

void PatientManager::onDelete(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/patient/delete", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
    }
    refresh();        
}
