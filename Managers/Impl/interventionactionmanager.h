#ifndef INTERVENTIONACTIONMANAGER_H
#define INTERVENTIONACTIONMANAGER_H

#include "Managers/genericmanager.h"
#include <QList>
#include "Model/Impl/interventionaction.h"

class InterventionActionManager : public GenericManager
{
    Q_OBJECT
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
    void onPermissionsChanged();
};

#endif // INTERVENTIONACTIONMANAGER_H
