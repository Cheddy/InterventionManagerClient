#ifndef INTERVENTIONDETAILFORM_H
#define INTERVENTIONDETAILFORM_H
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPlainTextEdit>
#include "Forms/abstractform.h"

class InterventionDetailForm : public AbstractForm
{
public:
    InterventionDetailForm(QListWidgetItem *item);
    QLineEdit *descriptionField;
    QPlainTextEdit *detailField;
    
public slots:
    void save(); 
};

#endif // INTERVENTIONDETAILFORM_H
