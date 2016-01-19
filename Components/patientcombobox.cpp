#include "patientcombobox.h"
#include "ui_patientcombobox.h"
#include "Model/Impl/patient.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>

PatientComboBox::PatientComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientComboBox)
{
    ui->setupUi(this);
}

PatientComboBox::~PatientComboBox()
{
    delete ui;
}

void PatientComboBox::on_refreshButton_clicked()
{
    ui->comboBox->setEnabled(false);
    QVariant var = ui->comboBox->currentData();
    Patient current = var.value<Patient>();
    emit countChanged(0);    
    ui->comboBox->clear();
    NetUtils net;
    QString html = net.get("http://localhost:8080/patient/all");
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

bool PatientComboBox::containPatients()
{
    return ui->comboBox->count() > 0;
}

void PatientComboBox::on_lineEdit_textChanged(const QString &text)
{
    int index = ui->comboBox->findText(text, Qt::MatchContains);
    if(index > 0 && index < ui->comboBox->count()){
        ui->comboBox->setCurrentIndex(index);
    }
}
