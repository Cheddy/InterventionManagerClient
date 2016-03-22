#include "filterselector.h"
#include "ui_filterselector.h"

FilterSelector::FilterSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterSelector)
{
    ui->setupUi(this);
}

FilterSelector::~FilterSelector()
{
    delete ui;
}

void FilterSelector::on_buttonBox_accepted()
{
    
}

void FilterSelector::on_removeButton_clicked()
{
    QList<QListWidgetItem *> list = ui->selectedFilters->selectedItems();
    if(!list.isEmpty()){
        delete list.takeFirst();
    }    
}
