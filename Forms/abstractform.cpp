#include "abstractform.h"
#include "ui_abstractform.h"

AbstractForm::AbstractForm(QListWidgetItem * item) :
    QDialog(),
    ui(new Ui::AbstractForm)
{
    ui->setupUi(this);
    this->item = item;
}

AbstractForm::~AbstractForm()
{
    delete ui;
}

void AbstractForm::on_buttonBox_accepted()
{
    save();
}
