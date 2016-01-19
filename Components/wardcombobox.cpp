#include "wardcombobox.h"
#include "ui_wardcombobox.h"
#include "Model/Impl/ward.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>

WardComboBox::WardComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WardComboBox)
{
    ui->setupUi(this);
}

WardComboBox::~WardComboBox()
{
    delete ui;
}

void WardComboBox::on_refreshButton_clicked()
{
    ui->comboBox->setEnabled(false);
    QVariant var = ui->comboBox->currentData();
    Ward current = var.value<Ward>();
    emit countChanged(0);    
    ui->comboBox->clear();
    NetUtils net;
    QString html = net.get("http://localhost:8080/ward/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Ward ward;
        ward.read(array[i].toObject());
        QVariant var;
        var.setValue(ward);
        ui->comboBox->addItem(ward.getName(), var);
    }
    if(current.getId() != -1){
        for(int i = 0; i < ui->comboBox->count(); i++){
            if(ui->comboBox->itemData(i).value<Ward>().getId() == current.getId()){
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }        
    }
    ui->comboBox->setEnabled(true);    
    emit countChanged(ui->comboBox->count());
}

Ward WardComboBox::getWard()
{
    QVariant var = ui->comboBox->currentData();
    return var.value<Ward>();
}

void WardComboBox::setWard(Ward ward)
{
    if(ward.getId() != -1){
        for(int i = 0; i < ui->comboBox->count(); i++){
            if(ui->comboBox->itemData(i).value<Ward>().getId() == ward.getId()){
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }        
    }
}

bool WardComboBox::containWards()
{
    return ui->comboBox->count() > 0;
}

void WardComboBox::on_lineEdit_textChanged(const QString &text)
{
    int index = ui->comboBox->findText(text, Qt::MatchContains);
    if(index > 0 && index < ui->comboBox->count()){
        ui->comboBox->setCurrentIndex(index);
    }
}
