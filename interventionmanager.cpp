#include "interventionmanager.h"
#include "ui_interventionmanager.h"
#include "Model/Impl/intervention.h"
#include "Forms/interventionform.h"
#include <QMessageBox>
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

InterventionManager::InterventionManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterventionManager)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);    
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    on_refreshButton_clicked();
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
        NetUtils net;
        int response = net.post("intervention/save", &intervention);  
        if(response != 202){
            QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
        }
        on_refreshButton_clicked();                    
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
        Intervention original = list[0]->data(Qt::UserRole).value<Intervention>();        
        InterventionForm *form = new InterventionForm(list);
        int code = form->exec();
        if(code == QDialog::Accepted){
            Intervention intervention = list[0]->data(Qt::UserRole).value<Intervention>();
            if(original != intervention){
                NetUtils net;
                int response = net.post("intervention/save", &intervention);  
                if(response != 202){
                    QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Editing Member");
                }
            }
        }
    }
}

void InterventionManager::on_deleteButton_clicked()
{
    QList<QTableWidgetItem *> list = ui->tableWidget->selectedItems();
    if(!list.isEmpty()){
        QTableWidgetItem *item = list.takeFirst();
        if(item != NULL){
            QVariant var = item->data(Qt::UserRole);   
            Intervention intervention = var.value<Intervention>();       
            NetUtils net;            
            int response = net.post("intervention/delete", &intervention);  
            if(response != 202){
                QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Deleting Member");
            }
            on_refreshButton_clicked();            
        }
    }
}

void InterventionManager::on_refreshButton_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    NetUtils net;
    QString html = net.get("intervention/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Intervention intervention;
        intervention.read(array[i].toObject());
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
        
        item->setText(intervention.getStaff().getDisplayName());
        list[1]->setText(intervention.getDateTime().toString("yyyy/MM/dd HH:mm:ss"));
        list[2]->setText(intervention.getVerifiedStaff().getDisplayName());
        list[3]->setText(intervention.getVerifiedDateTime().toString("yyyy/MM/dd HH:mm:ss"));
        list[4]->setText(intervention.getWard().getName());    
        list[5]->setText(intervention.getPatient().getDisplayName());  
        list[6]->setText(intervention.getDetailsList());  
        list[7]->setText(intervention.getActionsList());  
        list[8]->setText(intervention.getOutcomesList());  
        list[9]->setText(intervention.getCompletedStaff().getDisplayName());
        list[10]->setText(intervention.getCompletedDateTime().toString("yyyy/MM/dd HH:mm:ss"));
        list[11]->setText(intervention.getImpact().getName());
        
        ui->tableWidget->insertRow(0);
        for(int i = 0; i < list.length(); i++){
            ui->tableWidget->setItem(0,i,list[i]);            
        }
    }
}

void InterventionManager::on_viewButton_clicked()
{
#ifndef QT_NO_PRINTER    
    QList<QTableWidgetItem *> list = ui->tableWidget->selectedItems();
    if(!list.isEmpty() && list.length() == ui->tableWidget->columnCount()){        
        QPrinter printer(QPrinter::ScreenResolution);
        printer.setPaperSize(QPrinter::A4);    
        QPrintPreviewDialog preview(&printer, this);
        preview.setWindowFlags ( Qt::Window );
        connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreview(QPrinter *)));
        preview.exec();
    }
#endif    
}

void InterventionManager::printPreview(QPrinter *printer)
{
#ifndef QT_NO_PRINTER
    QList<QTableWidgetItem *> list = ui->tableWidget->selectedItems();
    if(!list.isEmpty() && list.length() == ui->tableWidget->columnCount()){        
        Intervention intervention = list[0]->data(Qt::UserRole).value<Intervention>();
        QString html = intervention.toString();
        QTextDocument *newDocument = new QTextDocument();
        newDocument->setHtml(html);
        newDocument->print(printer);
        delete newDocument;
    }
#endif
}
