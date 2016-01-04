#ifndef GENERICMANAGER_H
#define GENERICMANAGER_H

#include <QWidget>
#include "Model/datastructure.h"

namespace Ui {
class GenericManager;
}

class GenericManager : public QWidget
{
    Q_OBJECT
    
public:
    explicit GenericManager(QWidget *parent = 0);
    ~GenericManager();
    QList<DataStructure*> data;
    
public slots:
    virtual DataStructure* add() = 0;    
    virtual DataStructure* edit() = 0;   
    virtual DataStructure* deleteFunction() = 0;    
    virtual void refresh() = 0;                
    virtual void onAdd(DataStructure *structure) = 0;
    virtual void onEdit(DataStructure *structure) = 0;
    virtual void onDelete(DataStructure *structure) = 0;
    
private slots:
    void on_newButton_clicked();
    
    void on_editButton_clicked();
    
    void on_deleteButton_clicked();
    
    void on_refreshButton_clicked();
    
private:
    Ui::GenericManager *ui;
};

#endif // STAFFRANKMANAGER_H
