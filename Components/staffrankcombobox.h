#ifndef STAFFRANKCOMBOBOX_H
#define STAFFRANKCOMBOBOX_H

#include <QWidget>
#include "Model/Impl/staffrank.h"

namespace Ui {
class StaffRankComboBox;
}

class StaffRankComboBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit StaffRankComboBox(QWidget *parent = 0);
    ~StaffRankComboBox();
    StaffRank getStaffRank();
    void setStaffRank(StaffRank rank);
    void setStaffRankByName(StaffRank rank);    
    bool containStaffRanks();
    
public slots:
    void on_refreshButton_clicked();
    void onPermissionsChanged();
    
private:
    Ui::StaffRankComboBox *ui;
    
signals:
    void countChanged(int newCount);
private slots:
    void on_lineEdit_textChanged(const QString &text);
    void on_newButton_clicked();
};

#endif // STAFFRANKCOMBOBOX_H
