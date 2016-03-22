#include "logmanager.h"

#include "Model/Impl/log.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QList>
#include <QMessageBox>
#include "mainwindow.h"
#include <QDebug>

LogManager::LogManager()
{
    ui->horizontalLayout->removeWidget(ui->newButton);
    delete ui->newButton;
    ui->horizontalLayout->removeWidget(ui->editButton);
    delete ui->editButton;
    ui->deleteButton->setText("Clear");   
}

void LogManager::onPermissionsChanged()
{
 
}

void LogManager::add()
{    
}

void LogManager::view()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(!list.isEmpty()){
        QListWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            Log log = var.value<Log>();                   
            ViewDialog *viewDialog = new ViewDialog(&log);
            viewDialog->exec();
            delete viewDialog;  
        }
    }
}

void LogManager::edit()
{
}

void LogManager::deleteFunction()
{
    NetUtils net;
    net.get("log/clear");  
    refresh();
}

void LogManager::refresh()
{
    ui->listWidget->clear();
    NetUtils net;
    QString html = net.get("log/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Log log;
        log.read(array[i].toObject());
        QVariant var;
        var.setValue(log);
        QListWidgetItem *item = new QListWidgetItem(log.getDescription());
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

void LogManager::onAdd(DataStructure *structure)
{
}

void LogManager::onEdit(DataStructure *structure)
{
}

void LogManager::onDelete(DataStructure *structure)
{
}
