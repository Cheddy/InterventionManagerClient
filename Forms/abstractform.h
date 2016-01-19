#ifndef ABSTRACTFORM_H
#define ABSTRACTFORM_H

#include <QDialog>
#include <QListWidgetItem>
#include "ui_abstractform.h"

namespace Ui {
class AbstractForm;
}

class AbstractForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit AbstractForm(QListWidgetItem *item);
    ~AbstractForm();
    
public slots:
    virtual void save() = 0;    
    
protected:
    Ui::AbstractForm *ui;
    QListWidgetItem *item;
private slots:
    void on_buttonBox_accepted();
};

#endif // ABSTRACTFORM_H
