#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H

#include "Managers/genericmanager.h"

class StaffManager : public GenericManager
{
public:
    StaffManager();
    
public slots:
    void add();    
    void edit();   
    void deleteFunction();    
    void refresh();                
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
    
};

#endif // STAFFMANAGER_H
