#include "interventiondetailmanager.h"
#include "Network/netutils.h"
#include "Forms/Impl/interventiondetailform.h"

InterventionDetailManager::InterventionDetailManager()
{
    ui->gridLayout->setContentsMargins(0,0,0,0);    
    ui->horizontalLayout->removeWidget(ui->refreshButton);
    delete ui->refreshButton;
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
