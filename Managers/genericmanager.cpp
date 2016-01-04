#include "genericmanager.h"
#include "ui_genericmanager.h"

GenericManager::GenericManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenericManager)
{
    ui->setupUi(this);
}

GenericManager::~GenericManager()
{
    delete ui;
}

void GenericManager::on_newButton_clicked()
{
    onAdd(add());
}

void GenericManager::on_editButton_clicked()
{
    onEdit(edit());
}

void GenericManager::on_deleteButton_clicked()
{
    onDelete(deleteFunction());
}

void GenericManager::on_refreshButton_clicked()
{
    refresh();
}
