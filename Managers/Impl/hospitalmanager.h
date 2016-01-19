#ifndef HOSPITALMANAGER_H
#define HOSPITALMANAGER_H

#include "Managers/genericmanager.h"

class HospitalManager : public GenericManager
{
public:
    HospitalManager();
    
public slots:
    void add();    
    void edit();   
    void deleteFunction();    
    void refresh();                
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
    
};

#endif // HOSPITALMANAGER_H
