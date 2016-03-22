#include "interventiondetailmanager.h"
#include "Network/netutils.h"
#include "Forms/Impl/interventiondetailform.h"
#include "mainwindow.h"

InterventionDetailManager::InterventionDetailManager()
{
    ui->gridLayout->setContentsMargins(0,0,0,0);    
    ui->horizontalLayout->removeWidget(ui->refreshButton);
    delete ui->refreshButton;
    onPermissionsChanged();    
}

void InterventionDetailManager::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_INTERVENTION_DETAIL_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
    if((permissions & MainWindow::EDIT_INTERVENTION_DETAIL_PERMISSION) == 0){
        ui->editButton->setVisible(false);
    }else{
        ui->editButton->setVisible(true);
    }
    if((permissions & MainWindow::DELETE_INTERVENTION_DETAIL_PERMISSION) == 0){
        ui->deleteButton->setVisible(false);
    }else{
        ui->deleteButton->setVisible(true);
    }
}

void InterventionDetailManager::add()
{
    InterventionDetail detail;
    detail.setDescription("New Member");
    
    QVariant var;
    var.setValue(detail);
    QListWidgetItem *item = new QListWidgetItem(detail.getDescription());
    item->setData(Qt::UserRole, var);
    
    InterventionDetailForm *form = new InterventionDetailForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ui->listWidget->addItem(item);
        detail = var.value<InterventionDetail>();                
        onAdd(&detail);        
    }else{
        delete item;
    }
}

void InterventionDetailManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        InterventionDetailForm *form = new InterventionDetailForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            QVariant var = item->data(Qt::UserRole);   
            InterventionDetail detail = var.value<InterventionDetail>();        
            onEdit(&detail);
        }
        
    }
}

void InterventionDetailManager::deleteFunction()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            InterventionDetail detail = var.value<InterventionDetail>();  
            delete item;
            onDelete(&detail);
        }
    }
}


void InterventionDetailManager::add(QList<InterventionDetail> list)
{
    for(int i = 0; i < list.length(); i++){
        QVariant var;
        InterventionDetail detail = list[i];
        var.setValue(detail);
        QListWidgetItem *item = new QListWidgetItem(detail.getDescription());
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

QList<InterventionDetail> InterventionDetailManager::get()
{
    QList<InterventionDetail> list;
    for(int i = 0; i < ui->listWidget->count(); i++){
        QListWidgetItem *item = ui->listWidget->item(i);
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            list << var.value<InterventionDetail>();
        }
    }
    return list;
}

void InterventionDetailManager::view()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            InterventionDetail detail = var.value<InterventionDetail>();  
            ViewDialog *viewDialog = new ViewDialog(&detail);
            viewDialog->exec();
            delete viewDialog;  
            
        }
    }
}

void InterventionDetailManager::refresh()
{
    
}

void InterventionDetailManager::onAdd(DataStructure *structure)
{
            
}

void InterventionDetailManager::onEdit(DataStructure *structure)
{
   
}

void InterventionDetailManager::onDelete(DataStructure *structure)
{
            
}
