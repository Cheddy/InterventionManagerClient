#ifndef INTERVENTIONACTIONMANAGER_H
#define INTERVENTIONACTIONMANAGER_H

#include "Managers/genericmanager.h"
#include <QList>
#include "Model/Impl/interventionaction.h"

class InterventionActionManager : public GenericManager
{
public:
    InterventionActionManager();
    
public slots:
    void add(); 
    void add(QList<InterventionAction> list);
    QList<InterventionAction> get();
    void edit();   
    void deleteFunction();    
    void refresh();                
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
};

#endif // INTERVENTIONACTIONMANAGER_H
