#include "hospitalmanager.h"
#include "Model/Impl/hospital.h"
#include "Network/netutils.h"
#include "Forms/Impl/hospitalform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QList>
#include <QMessageBox>

HospitalManager::HospitalManager()
{
    refresh();
}

void HospitalManager::add()
{
    Hospital hospital;
    hospital.setName("New Member");
    QVariant var;
    var.setValue(hospital);
    QListWidgetItem *item = new QListWidgetItem(hospital.getName());
    item->setData(Qt::UserRole, var);
    
    
    HospitalForm *form = new HospitalForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ui->listWidget->addItem(item);
        hospital = var.value<Hospital>();                
        onAdd(&hospital);        
    }else{
        delete item;
    }
    
}

void HospitalManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        HospitalForm *form = new HospitalForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            QVariant var = item->data(Qt::UserRole);   
            Hospital hospital = var.value<Hospital>();        
            onEdit(&hospital);
        }
        
    }
}

void HospitalManager::deleteFunction()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            Hospital hospital = var.value<Hospital>();        
            onDelete(&hospital);
        }
    }
}

void HospitalManager::refresh()
{
    ui->listWidget->clear();
    NetUtils net;
    QString html = net.get("http://localhost:8080/hospital/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Hospital hospital;
        hospital.read(array[i].toObject());
        QVariant var;
        var.setValue(hospital);
        QListWidgetItem *item = new QListWidgetItem(hospital.getName());
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

void HospitalManager::onAdd(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/hospital/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void HospitalManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/hospital/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
}

void HospitalManager::onDelete(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/hospital/delete", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
    }
    refresh();        
}
