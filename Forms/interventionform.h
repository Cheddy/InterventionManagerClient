#ifndef INTERVENTIONFORM_H
#define INTERVENTIONFORM_H

#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QCheckBox>
#include "Components/patientcombobox.h"
#include "Components/wardcombobox.h"
#include "Components/impactcombobox.h"
#include "Managers/Impl/interventiondetailmanager.h"
#include "Managers/Impl/interventionactionmanager.h"
#include "Managers/Impl/interventionoutcomemanager.h"
#include <QTableWidgetItem>

namespace Ui {
class InterventionForm;
}

class InterventionForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit InterventionForm(QList<QTableWidgetItem *> list);
    ~InterventionForm();
    PatientComboBox *patientField;
    WardComboBox *wardField;
    QDateTimeEdit *dateTimeField;
    InterventionDetailManager *detailManagerField;    
    QCheckBox *verifiedField, *completedField;
    InterventionActionManager *actionManagerField;   
    InterventionOutcomeManager *outcomeManagerField;            
    ImpactComboBox *impactField;
    
private slots:
    void on_buttonBox_accepted();
    
private:
    QList<QTableWidgetItem *> list;    
    Ui::InterventionForm *ui;
};

#endif // INTERVENTIONFORM_H
