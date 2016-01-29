#include "hospitalcombobox.h"
#include "ui_hospitalcombobox.h"
#include "Model/Impl/hospital.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>
#include "Forms/Impl/hospitalform.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include "mainwindow.h"

HospitalComboBox::HospitalComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HospitalComboBox)
{
    ui->setupUi(this);
    onPermissionsChanged();    
}

HospitalComboBox::~HospitalComboBox()
{
    delete ui;
}

void HospitalComboBox::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_HOSPITAL_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
}

void HospitalComboBox::on_refreshButton_clicked()
{
    ui->comboBox->setEnabled(false);
    QVariant var = ui->comboBox->currentData();
    Hospital current = var.value<Hospital>();
    emit countChanged(0);    
    ui->comboBox->clear();
    NetUtils net;
    QString html = net.get("hospital/all");
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

void HospitalComboBox::setHospitalByName(Hospital hospital)
{
    for(int i = 0; i < ui->comboBox->count(); i++){
        if(ui->comboBox->itemData(i).value<Hospital>().getName() == hospital.getName()){
            ui->comboBox->setCurrentIndex(i);
            break;
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
    if(index > -1 && index < ui->comboBox->count()){
        ui->comboBox->setCurrentIndex(index);
    }
}

void HospitalComboBox::on_newButton_clicked()
{
    Hospital hospital;
    hospital.setName("New Member");
    QVariant var;
    var.setValue(hospital);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole, var);
    
    
    HospitalForm *form = new HospitalForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        hospital = var.value<Hospital>();                
        NetUtils net;
        int response = net.post("hospital/save", &hospital);  
        if(response != 202){
            QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
        }
        on_refreshButton_clicked();    
        setHospitalByName(hospital);
    }else{
        delete item;
    }
}
