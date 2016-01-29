#ifndef PATIENTCOMBOBOX_H
#define PATIENTCOMBOBOX_H

#include <QWidget>
#include "Model/Impl/patient.h"

namespace Ui {
class PatientComboBox;
}

class PatientComboBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit PatientComboBox(QWidget *parent = 0);
    ~PatientComboBox();
    Patient getPatient();
    void setPatient(Patient rank);
    void setPatientByRTX(Patient rank);    
    bool containPatients();
    
public slots:
    void on_refreshButton_clicked();
    void onPermissionsChanged();
    
private:
    Ui::PatientComboBox *ui;
    
signals:
    void countChanged(int newCount);
private slots:
    void on_lineEdit_textChanged(const QString &text);
    void on_newButton_clicked();
};

#endif // PATIENTCOMBOBOX_H
