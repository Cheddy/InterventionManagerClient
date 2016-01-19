#include "impactmanager.h"
#include "Model/Impl/impact.h"
#include "Network/netutils.h"
#include "Forms/Impl/impactform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QList>
#include <QMessageBox>

ImpactManager::ImpactManager()
{
    refresh();
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

void ImpactManager::edit()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        
        ImpactForm *form = new ImpactForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            QVariant var = item->data(Qt::UserRole);   
            Impact impact = var.value<Impact>();        
            onEdit(&impact);
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
    QString html = net.get("http://localhost:8080/impact/all");
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
    int response = net.post("http://localhost:8080/impact/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void ImpactManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/impact/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
}

void ImpactManager::onDelete(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/impact/delete", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
    }
    refresh();        
}
