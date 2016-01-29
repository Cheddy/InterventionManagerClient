#include "impactcombobox.h"
#include "ui_impactcombobox.h"
#include "Model/Impl/impact.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>
#include "Forms/Impl/impactform.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include "mainwindow.h"

ImpactComboBox::ImpactComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImpactComboBox)
{
    ui->setupUi(this);
    onPermissionsChanged();    
}

ImpactComboBox::~ImpactComboBox()
{
    delete ui;
}

void ImpactComboBox::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_IMPACT_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
}

void ImpactComboBox::on_refreshButton_clicked()
{
    ui->comboBox->setEnabled(false);
    QVariant var = ui->comboBox->currentData();
    Impact current = var.value<Impact>();
    emit countChanged(0);    
    ui->comboBox->clear();
    NetUtils net;
    QString html = net.get("impact/all");
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

void ImpactComboBox::setImpactByName(Impact impact)
{
    for(int i = 0; i < ui->comboBox->count(); i++){
        if(ui->comboBox->itemData(i).value<Impact>().getName() == impact.getName()){
            ui->comboBox->setCurrentIndex(i);
            break;
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
    if(index > -1 && index < ui->comboBox->count()){
        ui->comboBox->setCurrentIndex(index);
    }
}

void ImpactComboBox::on_newButton_clicked()
{
    Impact impact;
    impact.setName("New Member");
    QVariant var;
    var.setValue(impact);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole, var);
    
    
    ImpactForm *form = new ImpactForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        impact = var.value<Impact>();                
        NetUtils net;
        int response = net.post("impact/save", &impact);  
        if(response != 202){
            QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
        }
        on_refreshButton_clicked();    
        setImpactByName(impact);
    }else{
        delete item;
    }
}
