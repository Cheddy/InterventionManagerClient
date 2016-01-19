#include "staffmanager.h"
#include "Model/Impl/staff.h"
#include "Network/netutils.h"
#include "Forms/Impl/staffform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include "mainwindow.h"
#include <QProcess>
#include <QApplication>

StaffManager::StaffManager()
{
    refresh();
}

void StaffManager::add()
{
    Staff staff;
    staff.setSurname("New Member");
    staff.setOthernames("New Member");    
    staff.setUsername("username");
    
    QVariant var;
    var.setValue(staff);
    QListWidgetItem *item = new QListWidgetItem(staff.getDisplayName());
    item->setData(Qt::UserRole, var);
    
    StaffForm *form = new StaffForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ui->listWidget->addItem(item);
        staff = var.value<Staff>();                
        onAdd(&staff);        
    }else{
        delete item;
    }
}

void StaffManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        StaffForm *form = new StaffForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            QVariant var = item->data(Qt::UserRole);   
            Staff staff = var.value<Staff>();        
            onEdit(&staff);
        }
        
    }
}

void StaffManager::deleteFunction()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            Staff staff = var.value<Staff>();        
            onDelete(&staff);
        }
    }
}

void StaffManager::refresh()
{
    ui->listWidget->clear();
    NetUtils net;
    QString html = net.get("http://localhost:8080/staff/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Staff staff;
        staff.read(array[i].toObject());
        QVariant var;
        var.setValue(staff);
        QListWidgetItem *item = new QListWidgetItem(staff.getDisplayName());
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

void StaffManager::onAdd(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/staff/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void StaffManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/staff/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
    if(((Staff *) structure)->getId() == MainWindow::user.getId() && !((Staff *) structure)->getPasswordHash().isEmpty()){   
        MainWindow::user = *((Staff *) structure);
    }    
}

void StaffManager::onDelete(DataStructure *structure)
{
    if(((Staff *) structure)->getId() != MainWindow::user.getId()){
        NetUtils net;
        int response = net.post("http://localhost:8080/staff/delete", structure);  
        if(response != 202){
            QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
        }
        refresh();        
    }else{
        QMessageBox::warning(this, "Error!", "Cannot delete self");        
    }
}
