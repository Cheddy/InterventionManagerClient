#ifndef IMPACTMANAGER_H
#define IMPACTMANAGER_H

#include "Managers/genericmanager.h"

class ImpactManager : public GenericManager
{
    Q_OBJECT
public:
    ImpactManager();
    
public slots:
    void add(); 
    void view();    
    void edit();   
    void deleteFunction();    
    void refresh();                
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
    void onPermissionsChanged();
};

#endif // IMPACTMANAGER_H
