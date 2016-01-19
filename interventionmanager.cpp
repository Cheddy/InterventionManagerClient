#include "interventionmanager.h"
#include "ui_interventionmanager.h"
#include "Model/Impl/intervention.h"
#include "Forms/interventionform.h"

InterventionManager::InterventionManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterventionManager)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);    
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

InterventionManager::~InterventionManager()
{
    delete ui;
}

void InterventionManager::on_newButton_clicked()
{
    Intervention intervention;
    QVariant var;
    var.setValue(intervention);    
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    item->setData(Qt::UserRole, var);
    QList<QTableWidgetItem *> list;
    list << item;
    for(int i = 1; i < ui->tableWidget->columnCount(); i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);        
        list << item;        
    }
    
    InterventionForm *form = new InterventionForm(list);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ui->tableWidget->insertRow(0);
        for(int i = 0; i < list.length(); i++){
            ui->tableWidget->setItem(0,i,list[i]);            
        }
        intervention = var.value<Intervention>();                
    }else{
        for(int i = 0; i < list.length(); i++){
            delete list[i];
        }
    }
    
}

void InterventionManager::on_editButton_clicked()
{
    QList<QTableWidgetItem *> list = ui->tableWidget->selectedItems();
    if(!list.isEmpty() && list.length() == ui->tableWidget->columnCount()){        
        InterventionForm *form = new InterventionForm(list);
        int code = form->exec();
        if(code == QDialog::Accepted){

        }
    }
}
