#include "wardmanager.h"
#include "Model/Impl/ward.h"
#include "Network/netutils.h"
#include "Forms/Impl/wardform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QList>
#include <QMessageBox>

WardManager::WardManager()
{
    refresh();    
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
        
        WardForm *form = new WardForm(item);
        int code = form->exec();
        if(code == QDialog::Accepted){
            QVariant var = item->data(Qt::UserRole);   
            Ward ward = var.value<Ward>();        
            onEdit(&ward);
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
    QString html = net.get("http://localhost:8080/ward/all");
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
    int response = net.post("http://localhost:8080/ward/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
    }
    refresh();        
}

void WardManager::onEdit(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/ward/save", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member (Likely caused by existing member with the desired name)");
        refresh();    
    }
}

void WardManager::onDelete(DataStructure *structure)
{
    NetUtils net;
    int response = net.post("http://localhost:8080/ward/delete", structure);  
    if(response != 202){
        QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
    }
    refresh();        
}
