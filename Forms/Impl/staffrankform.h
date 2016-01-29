#ifndef STAFFRANKFORM_H
#define STAFFRANKFORM_H
#include <QLineEdit>
#include <QDoubleSpinBox>
#include "Forms/abstractform.h"
#include <QCheckBox>

class StaffRankForm : public AbstractForm
{
public:
    StaffRankForm(QListWidgetItem *item);
    QLineEdit *nameField;
    QCheckBox *newHospitalBox, *editHospitalBox, *deleteHospitalBox;
    QCheckBox *newImpactBox, *editImpactBox, *deleteImpactBox;
    QCheckBox *newPatientBox, *editPatientBox, *deletePatientBox;
    QCheckBox *newStaffBox, *editStaffBox, *deleteStaffBox;
    QCheckBox *newStaffRankBox, *editStaffRankBox, *deleteStaffRankBox;
    QCheckBox *newWardBox, *editWardBox, *deleteWardBox;
    QCheckBox *newInterventionBox, *editInterventionBox, *deleteInterventionBox;
    QCheckBox *newInterventionDetailBox, *editInterventionDetailBox, *deleteInterventionDetailBox;
    QCheckBox *newInterventionActionBox, *editInterventionActionBox, *deleteInterventionActionBox;
    QCheckBox *newInterventionOutcomeBox, *editInterventionOutcomeBox, *deleteInterventionOutcomeBox;
    
public slots:
    void save();
    void stateChanged();    
};

#endif // STAFFRANKFORM_H
