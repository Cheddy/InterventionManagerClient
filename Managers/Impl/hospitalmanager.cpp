#include "hospitalmanager.h"
#include "Model/Impl/hospital.h"
#include "Network/netutils.h"
#include "Forms/Impl/hospitalform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QList>
#include <QMessageBox>
#include "mainwindow.h"

HospitalManager::HospitalManager()
{
    onPermissionsChanged();
    refresh();
}

void HospitalManager::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_HOSPITAL_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
    if((permissions & MainWindow::EDIT_HOSPITAL_PERMISSION) == 0){
        ui->editButton->setVisible(false);
    }else{
        ui->editButton->setVisible(true);
    }
    if((permissions & MainWindow::DELETE_HOSPITAL_PERMISSION) == 0){
        ui->deleteButton->setVisible(false);
    }else{
        ui->deleteButton->setVisible(true);
    }
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
        
        QVariant var = item->data(Qt::UserRole);   
        Hospital original = var.value<Hospital>(); 
        
        HospitalForm *form = new HospitalForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            var = item->data(Qt::UserRole);   
            Hospital hospital = var.value<Hospital>();       
            if(original != hospital){
                onEdit(&hospital);
            }
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
    QString html = net.get("hospital/all");
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
    int response = net.post("hospital/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void HospitalManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("hospital/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
}

void HospitalManager::onDelete(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("hospital/delete", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
    }
    refresh();        
}
