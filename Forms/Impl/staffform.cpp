#include "staffform.h"
#include <QLabel>
#include <QPushButton>
#include <QCryptographicHash>
#include "Model/Impl/staff.h"

StaffForm::StaffForm(QListWidgetItem *item) : 
    AbstractForm(item)
{
    Staff staff = this->item->data(Qt::UserRole).value<Staff>();
    surnameField = new QLineEdit(staff.getSurname());
    othernamesField = new QLineEdit(staff.getOthernames());
    usernameField = new QLineEdit(staff.getUsername());    
    rankField = new StaffRankComboBox();
    connect(rankField, &StaffRankComboBox::countChanged, this, &StaffForm::onStaffRankCountChanged);
    rankField->on_refreshButton_clicked();    
    rankField->setStaffRank(staff.getRank());
    passwordField = new QLineEdit();        
    passwordField->setEchoMode(QLineEdit::Password);
    
    ui->formLayout->addRow(new QLabel("Surname"), surnameField);
    ui->formLayout->addRow(new QLabel("Other Names"), othernamesField);
    ui->formLayout->addRow(new QLabel("Username"), usernameField);    
    ui->formLayout->addRow(new QLabel("Rank"), rankField);    
    ui->formLayout->addRow(new QLabel("Password (Leave Blank To Leave It Unedited)"), passwordField);        
    surnameField->setFocus();
    
    setWindowTitle("Staff Form");
}

void StaffForm::save(){
    QVariant var = item->data(Qt::UserRole);   
    Staff staff = var.value<Staff>();
    staff.setSurname(surnameField->text());
    staff.setOthernames(othernamesField->text());
    staff.setUsername(usernameField->text().toLower());    
    staff.setRank(rankField->getStaffRank());
    
    if(!passwordField->text().isEmpty()){
        QByteArray data = QCryptographicHash::hash(passwordField->text().toUtf8(), QCryptographicHash::Sha256);
        staff.setPasswordHash(QString::fromUtf8(data.toHex()));
    }
    var.setValue(staff);
    item->setData(Qt::UserRole, var);
    item->setText(staff.getDisplayName());
}

void StaffForm::onStaffRankCountChanged(int newCount)
{
    if(newCount < 1){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }else{
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);        
    }
    
}


