#ifndef IMPACTCOMBOBOX_H
#define IMPACTCOMBOBOX_H

#include <QWidget>
#include "Model/Impl/impact.h"

namespace Ui {
class ImpactComboBox;
}

class ImpactComboBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit ImpactComboBox(QWidget *parent = 0);
    ~ImpactComboBox();
    Impact getImpact();
    void setImpact(Impact impact);
    void setImpactByName(Impact impact);    
    bool containImpacts();
    
public slots:
    void on_refreshButton_clicked();
    void onPermissionsChanged();
    
private:
    Ui::ImpactComboBox *ui;
    
signals:
    void countChanged(int newCount);
private slots:
    void on_lineEdit_textChanged(const QString &text);
    void on_newButton_clicked();
    void on_viewButton_clicked();
};

#endif // IMPACTCOMBOBOX_H
