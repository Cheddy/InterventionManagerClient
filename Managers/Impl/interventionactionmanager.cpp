#include "interventionactionmanager.h"
#include "Network/netutils.h"
#include "Forms/Impl/interventionactionform.h"
#include "mainwindow.h"

InterventionActionManager::InterventionActionManager()
{
    ui->gridLayout->setContentsMargins(0,0,0,0);
    ui->horizontalLayout->removeWidget(ui->refreshButton);
    delete ui->refreshButton;
    onPermissionsChanged();
}

void InterventionActionManager::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_INTERVENTION_ACTION_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
    if((permissions & MainWindow::EDIT_INTERVENTION_ACTION_PERMISSION) == 0){
        ui->editButton->setVisible(false);
    }else{
        ui->editButton->setVisible(true);
    }
    if((permissions & MainWindow::DELETE_INTERVENTION_ACTION_PERMISSION) == 0){
        ui->deleteButton->setVisible(false);
    }else{
        ui->deleteButton->setVisible(true);
    }
}

void InterventionActionManager::add()
{
    InterventionAction action;
    action.setDescription("New Member");
    action.setDateTime(QDateTime::currentDateTime());
    
    QVariant var;
    var.setValue(action);
    QListWidgetItem *item = new QListWidgetItem(action.getDescription());
    item->setData(Qt::UserRole, var);
    
    InterventionActionForm *form = new InterventionActionForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ui->listWidget->addItem(item);
        action = var.value<InterventionAction>();                
        onAdd(&action);        
    }else{
        delete item;
    }
}

void InterventionActionManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        InterventionActionForm *form = new InterventionActionForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            QVariant var = item->data(Qt::UserRole);   
            InterventionAction action = var.value<InterventionAction>();        
            onEdit(&action);
        }
        
    }
}

void InterventionActionManager::deleteFunction()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            InterventionAction action = var.value<InterventionAction>();  
            delete item;
            onDelete(&action);
        }
    }
}

void InterventionActionManager::add(QList<InterventionAction> list)
{
    for(int i = 0; i < list.length(); i++){
        QVariant var;
        InterventionAction action = list[i];
        var.setValue(action);
        QListWidgetItem *item = new QListWidgetItem(action.getDescription());
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

QList<InterventionAction> InterventionActionManager::get()
{
    QList<InterventionAction> list;
    for(int i = 0; i < ui->listWidget->count(); i++){
        QListWidgetItem *item = ui->listWidget->item(i);
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            list << var.value<InterventionAction>();
        }
    }
    return list;
}

void InterventionActionManager::refresh()
{
    
}

void InterventionActionManager::onAdd(DataStructure *structure)
{
            
}

void InterventionActionManager::onEdit(DataStructure *structure)
{
   
}

void InterventionActionManager::onDelete(DataStructure *structure)
{
            
}
