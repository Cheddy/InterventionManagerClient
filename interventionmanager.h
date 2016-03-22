#ifndef INTERVENTIONMANAGER_H
#define INTERVENTIONMANAGER_H

#include <QWidget>
#include <QPrinter>

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
    
    void on_deleteButton_clicked();
    
    void on_refreshButton_clicked();
    
    void on_viewButton_clicked();
    
    void printPreview(QPrinter *printer);
    
private:
    Ui::InterventionManager *ui;
};

#endif // INTERVENTIONMANAGER_H
