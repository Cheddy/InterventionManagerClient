#ifndef INTERVENTIONOUTCOMEFORM_H
#define INTERVENTIONOUTCOMEFORM_H
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPlainTextEdit>
#include "Forms/abstractform.h"

class InterventionOutcomeForm : public AbstractForm
{
public:
    InterventionOutcomeForm(QListWidgetItem *item);
    QLineEdit *descriptionField;
    QPlainTextEdit *detailField;
    QDateTimeEdit *dateTimeField;
    
public slots:
    void save();    
};

#endif // INTERVENTIONOUTCOMEFORM_H
