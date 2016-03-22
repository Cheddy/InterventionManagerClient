#include "staffrankmanager.h"
#include "Model/Impl/staffrank.h"
#include "Network/netutils.h"
#include "Forms/Impl/staffrankform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QList>
#include <QMessageBox>
#include "mainwindow.h"

StaffRankManager::StaffRankManager()
{
    onPermissionsChanged();
    refresh();
}

void StaffRankManager::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_STAFF_RANK_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
    if((permissions & MainWindow::EDIT_STAFF_RANK_PERMISSION) == 0){
        ui->editButton->setVisible(false);
    }else{
        ui->editButton->setVisible(true);
    }
    if((permissions & MainWindow::DELETE_STAFF_RANK_PERMISSION) == 0){
        ui->deleteButton->setVisible(false);
    }else{
        ui->deleteButton->setVisible(true);
    }
}

void StaffRankManager::add()
{
    StaffRank rank;
    rank.setName("New Member");
    rank.setPermissions(0LL);
    QVariant var;
    var.setValue(rank);
    QListWidgetItem *item = new QListWidgetItem(rank.getName());
    item->setData(Qt::UserRole, var);
    
    StaffRankForm *form = new StaffRankForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ui->listWidget->addItem(item);
        rank = var.value<StaffRank>();                
        onAdd(&rank);        
    }else{
        delete item;
    }
}

void StaffRankManager::view()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            StaffRank rank = var.value<StaffRank>();        
            ViewDialog *viewDialog = new ViewDialog(&rank);
            viewDialog->exec();
            delete viewDialog;  
        }
    }
}

void StaffRankManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        QVariant var = item->data(Qt::UserRole);   
        StaffRank original = var.value<StaffRank>();                
        
        StaffRankForm *form = new StaffRankForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            var = item->data(Qt::UserRole);   
            StaffRank rank = var.value<StaffRank>();        
            if(original != rank){
                onEdit(&rank);
            }
        }
        
    }
}

void StaffRankManager::deleteFunction()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            StaffRank rank = var.value<StaffRank>();
            onDelete(&rank);
        }
    }
}

void StaffRankManager::refresh()
{
    ui->listWidget->clear();
    NetUtils net;
    QString html = net.get("staffrank/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        StaffRank staffRank;
        staffRank.read(array[i].toObject());
        QVariant var;
        var.setValue(staffRank);
        QListWidgetItem *item = new QListWidgetItem(staffRank.getName());
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

void StaffRankManager::onAdd(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("staffrank/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void StaffRankManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("staffrank/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
    if(((StaffRank *)structure)->getId() == MainWindow::user.getRank().getId()){
        MainWindow::user.setRank(*((StaffRank *)structure));
        emit permissionsChanged();
    }
        
}

void StaffRankManager::onDelete(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("staffrank/delete", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
    }
    refresh();        
}
