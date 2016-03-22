#include "staffrankcombobox.h"
#include "ui_staffrankcombobox.h"
#include "Model/Impl/staffrank.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>
#include "Forms/Impl/staffrankform.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include "mainwindow.h"

StaffRankComboBox::StaffRankComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaffRankComboBox)
{
    ui->setupUi(this);
    onPermissionsChanged();    
}

StaffRankComboBox::~StaffRankComboBox()
{
    delete ui;
}

void StaffRankComboBox::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_STAFF_RANK_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
}

void StaffRankComboBox::on_refreshButton_clicked()
{
    ui->comboBox->setEnabled(false);
    QVariant var = ui->comboBox->currentData();
    StaffRank current = var.value<StaffRank>();
    emit countChanged(0);    
    ui->comboBox->clear();
    NetUtils net;
    QString html = net.get("staffrank/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        StaffRank rank;
        rank.read(array[i].toObject());
        QVariant var;
        var.setValue(rank);
        ui->comboBox->addItem(rank.getName(), var);
    }
    if(current.getId() != -1){
        for(int i = 0; i < ui->comboBox->count(); i++){
            if(ui->comboBox->itemData(i).value<StaffRank>().getId() == current.getId()){
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }        
    }
    ui->comboBox->setEnabled(true);    
    emit countChanged(ui->comboBox->count());
}

StaffRank StaffRankComboBox::getStaffRank()
{
    QVariant var = ui->comboBox->currentData();
    return var.value<StaffRank>();
}

void StaffRankComboBox::setStaffRank(StaffRank rank)
{
    if(rank.getId() != -1){
        for(int i = 0; i < ui->comboBox->count(); i++){
            if(ui->comboBox->itemData(i).value<StaffRank>().getId() == rank.getId()){
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }        
    }
}

void StaffRankComboBox::setStaffRankByName(StaffRank rank)
{
    for(int i = 0; i < ui->comboBox->count(); i++){
        if(ui->comboBox->itemData(i).value<StaffRank>().getName() == rank.getName()){
            ui->comboBox->setCurrentIndex(i);
            break;
        }
    }        
    
}

bool StaffRankComboBox::containStaffRanks()
{
    return ui->comboBox->count() > 0;
}

void StaffRankComboBox::on_lineEdit_textChanged(const QString &text)
{
    int index = ui->comboBox->findText(text, Qt::MatchContains);
    if(index > -1 && index < ui->comboBox->count()){
        ui->comboBox->setCurrentIndex(index);
    }
}

void StaffRankComboBox::on_newButton_clicked()
{
    StaffRank rank;
    rank.setName("New Member");
    rank.setPermissions(0LL);    
    QVariant var;
    var.setValue(rank);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole, var);
    
    
    StaffRankForm *form = new StaffRankForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        rank = var.value<StaffRank>();                
        NetUtils net;
        int response = net.post("staffrank/save", &rank);  
        if(response != 202){
            QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
        }
        on_refreshButton_clicked();    
        setStaffRankByName(rank);
    }else{
        delete item;
    }
}

void StaffRankComboBox::on_viewButton_clicked()
{
    QVariant var = ui->comboBox->currentData();
    StaffRank rank = var.value<StaffRank>();
    if(rank.getId() != -1){
        ViewDialog *viewDialog = new ViewDialog(&rank);
        viewDialog->exec();
        delete viewDialog;          
    }
}
