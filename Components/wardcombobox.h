#ifndef WARDCOMBOBOX_H
#define WARDCOMBOBOX_H

#include <QWidget>
#include "Model/Impl/ward.h"

namespace Ui {
class WardComboBox;
}

class WardComboBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit WardComboBox(QWidget *parent = 0);
    ~WardComboBox();
    Ward getWard();
    void setWard(Ward ward);
    void setWardByParameters(Ward ward);    
    bool containWards();
    
public slots:
    void on_refreshButton_clicked();
    void onPermissionsChanged();
    
private:
    Ui::WardComboBox *ui;
    
signals:
    void countChanged(int newCount);
private slots:
    void on_lineEdit_textChanged(const QString &text);
    void on_newButton_clicked();
    void on_viewButton_clicked();
};

#endif // WARDCOMBOBOX_H
