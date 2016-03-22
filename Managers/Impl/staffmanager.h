#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H

#include "Managers/genericmanager.h"

class StaffManager : public GenericManager
{
    Q_OBJECT
public:
    StaffManager();
    
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

#endif // STAFFMANAGER_H
