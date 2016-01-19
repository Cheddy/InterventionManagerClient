#include "hospitalcombobox.h"
#include "ui_hospitalcombobox.h"
#include "Model/Impl/hospital.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>

HospitalComboBox::HospitalComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HospitalComboBox)
{
    ui->setupUi(this);
}

HospitalComboBox::~HospitalComboBox()
{
    delete ui;
}

void HospitalComboBox::on_refreshButton_clicked()
{
    ui->comboBox->setEnabled(false);
    QVariant var = ui->comboBox->currentData();
    Hospital current = var.value<Hospital>();
    emit countChanged(0);    
    ui->comboBox->clear();
    NetUtils net;
    QString html = net.get("http://localhost:8080/hospital/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Hospital hospital;
        hospital.read(array[i].toObject());
        QVariant var;
        var.setValue(hospital);
        ui->comboBox->addItem(hospital.getName(), var);
    }
    if(current.getId() != -1){
        for(int i = 0; i < ui->comboBox->count(); i++){
            if(ui->comboBox->itemData(i).value<Hospital>().getId() == current.getId()){
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }        
    }
    ui->comboBox->setEnabled(true);    
    emit countChanged(ui->comboBox->count());
}

Hospital HospitalComboBox::getHospital()
{
    QVariant var = ui->comboBox->currentData();
    return var.value<Hospital>();
}

void HospitalComboBox::setHospital(Hospital hospital)
{
    if(hospital.getId() != -1){
        for(int i = 0; i < ui->comboBox->count(); i++){
            if(ui->comboBox->itemData(i).value<Hospital>().getId() == hospital.getId()){
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }        
    }
}

bool HospitalComboBox::containHospitals()
{
    return ui->comboBox->count() > 0;
}

void HospitalComboBox::on_lineEdit_textChanged(const QString &text)
{
    int index = ui->comboBox->findText(text, Qt::MatchContains);
    if(index > 0 && index < ui->comboBox->count()){
        ui->comboBox->setCurrentIndex(index);
    }
}
