#ifndef HOSPITALMANAGER_H
#define HOSPITALMANAGER_H

#include "Managers/genericmanager.h"

class HospitalManager : public GenericManager
{
    Q_OBJECT
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
    void onPermissionsChanged();
};

#endif // HOSPITALMANAGER_H
