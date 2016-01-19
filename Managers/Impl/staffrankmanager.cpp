#include "staffrankmanager.h"
#include "Model/Impl/staffrank.h"
#include "Network/netutils.h"
#include "Forms/Impl/staffrankform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QList>
#include <QMessageBox>

StaffRankManager::StaffRankManager()
{
    refresh();
}

void StaffRankManager::add()
{
    StaffRank rank;
    rank.setName("New Member");
    rank.setPermissions(INT32_MAX);
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

void StaffRankManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        StaffRankForm *form = new StaffRankForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            QVariant var = item->data(Qt::UserRole);   
            StaffRank rank = var.value<StaffRank>();        
            onEdit(&rank);
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
    QString html = net.get("http://localhost:8080/staffrank/all");
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
    int response = net.post("http://localhost:8080/staffrank/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void StaffRankManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/staffrank/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
}

void StaffRankManager::onDelete(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/staffrank/delete", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
    }
    refresh();        
}
