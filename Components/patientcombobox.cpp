#include "patientcombobox.h"
#include "ui_patientcombobox.h"
#include "Model/Impl/patient.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>
#include "Forms/Impl/patientform.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include "mainwindow.h"

PatientComboBox::PatientComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientComboBox)
{
    ui->setupUi(this);
    onPermissionsChanged();    
}

PatientComboBox::~PatientComboBox()
{
    delete ui;
}

void PatientComboBox::onPermissionsChanged()
{
    long long permissions = MainWindow::user.getRank().getPermissions();    
    if((permissions & MainWindow::NEW_PATIENT_PERMISSION) == 0){
        ui->newButton->setVisible(false);
    }else{
        ui->newButton->setVisible(true);        
    }
}

void PatientComboBox::on_refreshButton_clicked()
{
    ui->comboBox->setEnabled(false);
    QVariant var = ui->comboBox->currentData();
    Patient current = var.value<Patient>();
    emit countChanged(0);    
    ui->comboBox->clear();
    NetUtils net;
    QString html = net.get("patient/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    for(int i = 0; i < array.size(); i++){
        Patient patient;
        patient.read(array[i].toObject());
        QVariant var;
        var.setValue(patient);
        ui->comboBox->addItem(patient.getDisplayName(), var);
    }
    if(current.getId() != -1){
        for(int i = 0; i < ui->comboBox->count(); i++){
            if(ui->comboBox->itemData(i).value<Patient>().getId() == current.getId()){
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }        
    }
    ui->comboBox->setEnabled(true);    
    emit countChanged(ui->comboBox->count());
}

Patient PatientComboBox::getPatient()
{
    QVariant var = ui->comboBox->currentData();
    return var.value<Patient>();
}

void PatientComboBox::setPatient(Patient patient)
{
    if(patient.getId() != -1){
        for(int i = 0; i < ui->comboBox->count(); i++){
            if(ui->comboBox->itemData(i).value<Patient>().getId() == patient.getId()){
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }        
    }
}

void PatientComboBox::setPatientByRTX(Patient patient)
{
    for(int i = 0; i < ui->comboBox->count(); i++){
        if(ui->comboBox->itemData(i).value<Patient>().getRtx() == patient.getRtx()){
            ui->comboBox->setCurrentIndex(i);
            break;
        }
    }        
    
}

bool PatientComboBox::containPatients()
{
    return ui->comboBox->count() > 0;
}

void PatientComboBox::on_lineEdit_textChanged(const QString &text)
{
    int index = ui->comboBox->findText(text, Qt::MatchContains);
    if(index > -1 && index < ui->comboBox->count()){
        ui->comboBox->setCurrentIndex(index);
    }
}

void PatientComboBox::on_newButton_clicked()
{
    Patient patient;
    patient.setSurname("New Member");
    patient.setOthernames("New Member");    
    QVariant var;
    var.setValue(patient);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole, var);
    
    
    PatientForm *form = new PatientForm(item);
    int code = form->exec();
    if(code == QDialog::Accepted){
        var = item->data(Qt::UserRole);   
        patient = var.value<Patient>();                
        NetUtils net;
        int response = net.post("patient/save", &patient);  
        if(response != 202){
            QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Adding New Member (Likely caused by existing member with the name \"New Member\")");
        }
        on_refreshButton_clicked();    
        setPatientByRTX(patient);
    }else{
        delete item;
    }
}

void PatientComboBox::on_viewButton_clicked()
{
    QVariant var = ui->comboBox->currentData();
    Patient patient = var.value<Patient>();
    if(patient.getId() != -1){
        ViewDialog *viewDialog = new ViewDialog(&patient);
        viewDialog->exec();
        delete viewDialog;          
    }
}
