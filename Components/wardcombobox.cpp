#include "wardcombobox.h"
#include "ui_wardcombobox.h"
#include "Model/Impl/ward.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>
#include "Model/Impl/hospital.h"
#include "Forms/Impl/wardform.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include "mainwindow.h"

WardComboBox::WardComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WardComboBox)
{
    ui->setupUi(this);
    onPermissionsChanged();
}

WardComboBox::~WardComboBox()
{
    delete ui;
}

void WardComboBox::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_WARD_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
}

void WardComboBox::on_refreshButton_clicked()
{
    ui->comboBox->setEnabled(false);
    QVariant var = ui->comboBox->currentData();
    Ward current = var.value<Ward>();
    emit countChanged(0);    
    ui->comboBox->clear();
    NetUtils net;
    QString html = net.get("ward/all");
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

void WardComboBox::setWardByParameters(Ward ward)
{
    for(int i = 0; i < ui->comboBox->count(); i++){
        if(ui->comboBox->itemData(i).value<Ward>().getHospital().getId() == ward.getHospital().getId() && ui->comboBox->itemData(i).value<Ward>().getName() == ward.getName()){
            ui->comboBox->setCurrentIndex(i);
            break;
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
    if(index > -1 && index < ui->comboBox->count()){
        ui->comboBox->setCurrentIndex(index);
    }
}

void WardComboBox::on_newButton_clicked()
{
    Ward ward;
    ward.setName("New Member");
    QVariant var;
    var.setValue(ward);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole, var);
    
    
    WardForm *form = new WardForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        ward = var.value<Ward>();                
        NetUtils net;
        int response = net.post("ward/save", &ward);  
        if(response != 202){
            QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
        }
        on_refreshButton_clicked();    
        setWardByParameters(ward);
    }else{
        delete item;
    }
}
