#ifndef IMPACTMANAGER_H
#define IMPACTMANAGER_H

#include "Managers/genericmanager.h"

class ImpactManager : public GenericManager
{
public:
    ImpactManager();
    
public slots:
    void add();    
    void edit();   
    void deleteFunction();    
    void refresh();                
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
    
};

#endif // IMPACTMANAGER_H
