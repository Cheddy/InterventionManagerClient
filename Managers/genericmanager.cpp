#include "genericmanager.h"
#include "viewdialog.h"

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
    add();
}

void GenericManager::on_editButton_clicked()
{
    edit();
}

void GenericManager::on_deleteButton_clicked()
{
    deleteFunction();
}

void GenericManager::on_refreshButton_clicked()
{
    refresh();
}

void GenericManager::on_viewButton_clicked()
{
    view();
}
