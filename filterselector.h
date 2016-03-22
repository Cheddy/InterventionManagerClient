#ifndef FILTERSELECTOR_H
#define FILTERSELECTOR_H

#include <QDialog>

namespace Ui {
class FilterSelector;
}

class FilterSelector : public QDialog
{
    Q_OBJECT
    
public:
    explicit FilterSelector(QWidget *parent = 0);
    ~FilterSelector();
    
private slots:
    void on_buttonBox_accepted();
    
    void on_removeButton_clicked();
    
private:
    Ui::FilterSelector *ui;
};

#endif // FILTERSELECTOR_H
