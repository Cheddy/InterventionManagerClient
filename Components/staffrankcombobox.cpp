#include "staffrankcombobox.h"
#include "ui_staffrankcombobox.h"
#include "Model/Impl/staffrank.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>

StaffRankComboBox::StaffRankComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaffRankComboBox)
{
    ui->setupUi(this);
}

StaffRankComboBox::~StaffRankComboBox()
{
    delete ui;
}

void StaffRankComboBox::on_refreshButton_clicked()
{
    ui->comboBox->setEnabled(false);
    QVariant var = ui->comboBox->currentData();
    StaffRank current = var.value<StaffRank>();
    emit countChanged(0);    
    ui->comboBox->clear();
    NetUtils net;
    QString html = net.get("http://localhost:8080/staffrank/all");
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

bool StaffRankComboBox::containStaffRanks()
{
    return ui->comboBox->count() > 0;
}

void StaffRankComboBox::on_lineEdit_textChanged(const QString &text)
{
    int index = ui->comboBox->findText(text, Qt::MatchContains);
    if(index > 0 && index < ui->comboBox->count()){
        ui->comboBox->setCurrentIndex(index);
    }
}
