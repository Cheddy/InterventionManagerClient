#ifndef STAFFRANKMANAGER_H
#define STAFFRANKMANAGER_H

#include "Managers/genericmanager.h"

class StaffRankManager : public GenericManager
{
public:
    StaffRankManager();
    
public slots:
    DataStructure* add();    
    DataStructure* edit();   
    DataStructure* deleteFunction();    
    void refresh();                
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
    
};

#endif // STAFFRANKMANAGER_H
