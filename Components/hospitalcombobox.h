#ifndef HOSPITALCOMBOBOX_H
#define HOSPITALCOMBOBOX_H

#include <QWidget>
#include "Model/Impl/hospital.h"

namespace Ui {
class HospitalComboBox;
}

class HospitalComboBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit HospitalComboBox(QWidget *parent = 0);
    ~HospitalComboBox();
    Hospital getHospital();
    void setHospital(Hospital hospital);
    void setHospitalByName(Hospital hospital);    
    bool containHospitals();
    
public slots:
    void on_refreshButton_clicked();
    void onPermissionsChanged();
private:
    Ui::HospitalComboBox *ui;
    
signals:
    void countChanged(int newCount);
private slots:
    void on_lineEdit_textChanged(const QString &text);
    void on_newButton_clicked();
};

#endif // HOSPITALCOMBOBOX_H
