#ifndef STAFFRANKMANAGER_H
#define STAFFRANKMANAGER_H

#include "Managers/genericmanager.h"

class StaffRankManager : public GenericManager
{
public:
    StaffRankManager();
    
public slots:
    void add();    
    void edit();   
    void deleteFunction();    
    void refresh();                
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
    
};

#endif // STAFFRANKMANAGER_H
