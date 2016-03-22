#include "viewdialog.h"
#include "ui_viewdialog.h"

ViewDialog::ViewDialog(DataStructure *structure) :
    QDialog(),
    ui(new Ui::ViewDialog)
{
    ui->setupUi(this);
    ui->textEdit->setHtml(structure->toString());
}

ViewDialog::~ViewDialog()
{
    delete ui;
}
