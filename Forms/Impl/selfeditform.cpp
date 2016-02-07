#include "selfeditform.h"
#include <QLabel>
#include <QPushButton>
#include <QCryptographicHash>
#include "Model/Impl/staff.h"
#include "mainwindow.h"
#include "Network/netutils.h"
#include <QMessageBox>

SelfEditForm::SelfEditForm()
{
    surnameField = new QLineEdit(MainWindow::user.getSurname());
    othernamesField = new QLineEdit(MainWindow::user.getOthernames());
    
    passwordField = new QLineEdit();        
    passwordField->setEchoMode(QLineEdit::Password);
    
    ui->formLayout->addRow(new QLabel("Surname"), surnameField);
    ui->formLayout->addRow(new QLabel("Other Names"), othernamesField);
    ui->formLayout->addRow(new QLabel("Password (Leave Blank To Leave It Unedited)"), passwordField);        
    surnameField->setFocus();
    
    setWindowTitle("Edit User");
}

void SelfEditForm::save(){
    Staff staff = MainWindow::user;
    staff.setSurname(surnameField->text().trimmed());
    staff.setOthernames(othernamesField->text().trimmed());
    if(!passwordField->text().isEmpty()){
        QByteArray data = QCryptographicHash::hash(passwordField->text().toUtf8(), QCryptographicHash::Sha256);
        staff.setPasswordHash(QString::fromUtf8(data.toHex()));
    }
    staff.setUsername(MainWindow::user.getUsername());
    staff.setRank(MainWindow::user.getRank());
    if(staff.getOthernames() != MainWindow::user.getOthernames() || staff.getSurname() != MainWindow::user.getSurname() || staff.getPasswordHash() != MainWindow::user.getPasswordHash()){
        NetUtils net;
        int response = net.post("staff/save", &staff);  
        if(response != 202){
            QMessageBox::warning(this, "Error!", "Error Code: " + QString::number(response) + "\nError Submitting Edit");
        }else{
            MainWindow::user.setSurname(staff.getSurname());
            MainWindow::user.setOthernames(staff.getOthernames());
            if(!staff.getPasswordHash().isEmpty()){
                MainWindow::user.setPasswordHash(staff.getPasswordHash());
            }
        }
    }    
}

