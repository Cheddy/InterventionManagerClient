#include "staffrankform.h"
#include <QLabel>
#include "Model/Impl/staffrank.h"

StaffRankForm::StaffRankForm(QListWidgetItem *item) : 
    AbstractForm(item)
{
    nameField = new QLineEdit(this->item->data(Qt::UserRole).value<StaffRank>().getName());
    permissionField = new QSpinBox();
    permissionField->setMaximum(INT32_MAX);
    permissionField->setMinimum(0);
    permissionField->setValue(this->item->data(Qt::UserRole).value<StaffRank>().getPermissions());
    
    ui->formLayout->addRow(new QLabel("Name"), nameField);
    ui->formLayout->addRow(new QLabel("Permissions"), permissionField);    
    nameField->setFocus();    
    
    setWindowTitle("Staff Rank Form");
}

void StaffRankForm::save(){
    QVariant var = item->data(Qt::UserRole);   
    StaffRank rank = var.value<StaffRank>();
    rank.setName(nameField->text());
    rank.setPermissions(permissionField->value());
    var.setValue(rank);
    item->setData(Qt::UserRole, var);
    item->setText(rank.getName());
}
