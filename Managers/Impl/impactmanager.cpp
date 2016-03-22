#include "impactmanager.h"
#include "Model/Impl/impact.h"
#include "Network/netutils.h"
#include "Forms/Impl/impactform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QList>
#include <QMessageBox>
#include "mainwindow.h"

ImpactManager::ImpactManager()
{
    onPermissionsChanged();
    refresh();
}

void ImpactManager::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_IMPACT_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
    if((permissions & MainWindow::EDIT_IMPACT_PERMISSION) == 0){
        ui->editButton->setVisible(false);
    }else{
        ui->editButton->setVisible(true);
    }
    if((permissions & MainWindow::DELETE_IMPACT_PERMISSION) == 0){
        ui->deleteButton->setVisible(false);
    }else{
        ui->deleteButton->setVisible(true);
    }
}

void ImpactManager::add()
{
    Impact impact;
    impact.setName("New Member");
    QVariant var;
    var.setValue(impact);
    QListWidgetItem *item = new QListWidgetItem(impact.getName());
    item->setData(Qt::UserRole, var);
    
    
    ImpactForm *form = new ImpactForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ui->listWidget->addItem(item);
        impact = var.value<Impact>();                
        onAdd(&impact);        
    }else{
        delete item;
    }
    
}

void ImpactManager::view()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            Impact impact = var.value<Impact>();      
            ViewDialog *viewDialog = new ViewDialog(&impact);
            viewDialog->exec();
            delete viewDialog;  
            
        }
    }
}

void ImpactManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        QVariant var = item->data(Qt::UserRole);   
        Impact original = var.value<Impact>();                
        
        ImpactForm *form = new ImpactForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            var = item->data(Qt::UserRole);   
            Impact impact = var.value<Impact>();      
            if(original != impact){
                onEdit(&impact);
            }
        }
        
    }
}

void ImpactManager::deleteFunction()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            Impact impact = var.value<Impact>();        
            onDelete(&impact);
        }
    }
}

void ImpactManager::refresh()
{
    ui->listWidget->clear();
    NetUtils net;
    QString html = net.get("impact/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Impact impact;
        impact.read(array[i].toObject());
        QVariant var;
        var.setValue(impact);
        QListWidgetItem *item = new QListWidgetItem(impact.getName());
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

void ImpactManager::onAdd(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("impact/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void ImpactManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("impact/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
}

void ImpactManager::onDelete(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("impact/delete", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
    }
    refresh();        
}
