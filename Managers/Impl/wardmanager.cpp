#include "wardmanager.h"
#include "Model/Impl/ward.h"
#include "Network/netutils.h"
#include "Forms/Impl/wardform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include "mainwindow.h"

WardManager::WardManager()
{
    onPermissionsChanged();
    refresh();    
}

void WardManager::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_WARD_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
    if((permissions & MainWindow::EDIT_WARD_PERMISSION) == 0){
        ui->editButton->setVisible(false);
    }else{
        ui->editButton->setVisible(true);
    }
    if((permissions & MainWindow::DELETE_WARD_PERMISSION) == 0){
        ui->deleteButton->setVisible(false);
    }else{
        ui->deleteButton->setVisible(true);
    }
}


void WardManager::add()
{
    Ward ward;
    ward.setName("New Member");
    QVariant var;
    var.setValue(ward);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole, var);

    WardForm *form = new WardForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ui->listWidget->addItem(item);
        ward = var.value<Ward>();                
        onAdd(&ward);        
    }else{
        delete item;
    }
}

void WardManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        QVariant var = item->data(Qt::UserRole);   
        Ward original = var.value<Ward>();                
        
        WardForm *form = new WardForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            var = item->data(Qt::UserRole);   
            Ward ward = var.value<Ward>();        
            if(original != ward){
                onEdit(&ward);
            }
        }
        
    }
}

void WardManager::deleteFunction()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            Ward ward = var.value<Ward>();
            onDelete(&ward);
        }
    }
}

void WardManager::refresh()
{
    ui->listWidget->clear();
    NetUtils net;
    QString html = net.get("ward/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Ward ward;
        ward.read(array[i].toObject());
        QVariant var;
        var.setValue(ward);
        QListWidgetItem *item = new QListWidgetItem(ward.getName());
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

void WardManager::onAdd(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("ward/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void WardManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("ward/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
}

void WardManager::onDelete(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("ward/delete", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
    }
    refresh();        
}
