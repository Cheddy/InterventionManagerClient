#ifndef INTERVENTIONMANAGER_H
#define INTERVENTIONMANAGER_H

#include <QWidget>

namespace Ui {
class InterventionManager;
}

class InterventionManager : public QWidget
{
    Q_OBJECT
    
public:
    explicit InterventionManager(QWidget *parent = 0);
    ~InterventionManager();
    
private slots:
    void on_newButton_clicked();
    
    void on_editButton_clicked();
    
private:
    Ui::InterventionManager *ui;
};

#endif // INTERVENTIONMANAGER_H
