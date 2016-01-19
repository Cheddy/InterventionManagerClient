#ifndef INTERVENTIONDETAILMANAGER_H
#define INTERVENTIONDETAILMANAGER_H

#include "Managers/genericmanager.h"
#include <QList>
#include "Model/Impl/interventiondetail.h"

class InterventionDetailManager : public GenericManager
{
public:
    InterventionDetailManager();
    
public slots:
    void add();  
    void add(QList<InterventionDetail> list);
    QList<InterventionDetail> get();    
    void edit();   
    void deleteFunction();    
    void refresh();                
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
    
};

#endif // INTERVENTIONDETAILMANAGER_H
