#ifndef WARDMANAGER_H
#define WARDMANAGER_H

#include "Managers/genericmanager.h"

class WardManager : public GenericManager
{
public:
    WardManager();
    
public slots:
    void add();    
    void edit();   
    void deleteFunction();    
    void refresh();                
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
    
};

#endif // WARDMANAGER_H
