#include "interventionoutcomemanager.h"
#include "Network/netutils.h"
#include "Forms/Impl/interventionoutcomeform.h"
#include "mainwindow.h"

InterventionOutcomeManager::InterventionOutcomeManager()
{
    ui->gridLayout->setContentsMargins(0,0,0,0);        
    ui->horizontalLayout->removeWidget(ui->refreshButton);
    delete ui->refreshButton;
    onPermissionsChanged();
}

void InterventionOutcomeManager::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_INTERVENTION_OUTCOME_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
    if((permissions & MainWindow::EDIT_INTERVENTION_OUTCOME_PERMISSION) == 0){
        ui->editButton->setVisible(false);
    }else{
        ui->editButton->setVisible(true);
    }
    if((permissions & MainWindow::DELETE_INTERVENTION_OUTCOME_PERMISSION) == 0){
        ui->deleteButton->setVisible(false);
    }else{
        ui->deleteButton->setVisible(true);
    }
}

void InterventionOutcomeManager::add()
{
    InterventionOutcome outcome;
    outcome.setDescription("New Member");
    outcome.setDateTime(QDateTime::currentDateTime());
    
    QVariant var;
    var.setValue(outcome);
    QListWidgetItem *item = new QListWidgetItem(outcome.getDescription());
    item->setData(Qt::UserRole, var);
    
    InterventionOutcomeForm *form = new InterventionOutcomeForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ui->listWidget->addItem(item);
        outcome = var.value<InterventionOutcome>();                
        onAdd(&outcome);        
    }else{
        delete item;
    }
}

void InterventionOutcomeManager::view()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            InterventionOutcome outcome = var.value<InterventionOutcome>();        
            ViewDialog *viewDialog = new ViewDialog(&outcome);
            viewDialog->exec();
            delete viewDialog;  
            
        }
    }
}

void InterventionOutcomeManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        InterventionOutcomeForm *form = new InterventionOutcomeForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            QVariant var = item->data(Qt::UserRole);   
            InterventionOutcome outcome = var.value<InterventionOutcome>();        
            onEdit(&outcome);
        }
        
    }
}

void InterventionOutcomeManager::deleteFunction()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            InterventionOutcome outcome = var.value<InterventionOutcome>();  
            delete item;
            onDelete(&outcome);
        }
    }
}

void InterventionOutcomeManager::add(QList<InterventionOutcome> list)
{
    for(int i = 0; i < list.length(); i++){
        QVariant var;
        InterventionOutcome outcome = list[i];
        var.setValue(outcome);
        QListWidgetItem *item = new QListWidgetItem(outcome.getDescription());
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

QList<InterventionOutcome> InterventionOutcomeManager::get()
{
    QList<InterventionOutcome> list;
    for(int i = 0; i < ui->listWidget->count(); i++){
        QListWidgetItem *item = ui->listWidget->item(i);
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            list << var.value<InterventionOutcome>();
        }
    }
    return list;
}

void InterventionOutcomeManager::refresh()
{
    
}

void InterventionOutcomeManager::onAdd(DataStructure *structure)
{
            
}

void InterventionOutcomeManager::onEdit(DataStructure *structure)
{
   
}

void InterventionOutcomeManager::onDelete(DataStructure *structure)
{
            
}
