#ifndef INTERVENTIONACTIONFORM_H
#define INTERVENTIONACTIONFORM_H
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPlainTextEdit>
#include "Forms/abstractform.h"

class InterventionActionForm : public AbstractForm
{
public:
    InterventionActionForm(QListWidgetItem *item);
    QLineEdit *descriptionField;
    QPlainTextEdit *detailField;
    QDateTimeEdit *dateTimeField;
    
public slots:
    void save();    
};

#endif // INTERVENTIONACTIONFORM_H
