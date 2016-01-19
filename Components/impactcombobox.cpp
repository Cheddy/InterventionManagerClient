#include "impactcombobox.h"
#include "ui_impactcombobox.h"
#include "Model/Impl/impact.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>

ImpactComboBox::ImpactComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImpactComboBox)
{
    ui->setupUi(this);
}

ImpactComboBox::~ImpactComboBox()
{
    delete ui;
}

void ImpactComboBox::on_refreshButton_clicked()
{
    ui->comboBox->setEnabled(false);
    QVariant var = ui->comboBox->currentData();
    Impact current = var.value<Impact>();
    emit countChanged(0);    
    ui->comboBox->clear();
    NetUtils net;
    QString html = net.get("http://localhost:8080/impact/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Impact impact;
        impact.read(array[i].toObject());
        QVariant var;
        var.setValue(impact);
        ui->comboBox->addItem(impact.getName(), var);
    }
    if(current.getId() != -1){
        for(int i = 0; i < ui->comboBox->count(); i++){
            if(ui->comboBox->itemData(i).value<Impact>().getId() == current.getId()){
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }        
    }
    ui->comboBox->setEnabled(true);    
    emit countChanged(ui->comboBox->count());
}

Impact ImpactComboBox::getImpact()
{
    QVariant var = ui->comboBox->currentData();
    return var.value<Impact>();
}

void ImpactComboBox::setImpact(Impact impact)
{
    if(impact.getId() != -1){
        for(int i = 0; i < ui->comboBox->count(); i++){
            if(ui->comboBox->itemData(i).value<Impact>().getId() == impact.getId()){
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }        
    }
}

bool ImpactComboBox::containImpacts()
{
    return ui->comboBox->count() > 0;
}

void ImpactComboBox::on_lineEdit_textChanged(const QString &text)
{
    int index = ui->comboBox->findText(text, Qt::MatchContains);
    if(index > 0 && index < ui->comboBox->count()){
        ui->comboBox->setCurrentIndex(index);
    }
}
