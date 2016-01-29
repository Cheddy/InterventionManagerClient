#ifndef STAFFRANKMANAGER_H
#define STAFFRANKMANAGER_H

#include "Managers/genericmanager.h"

class StaffRankManager : public GenericManager
{
    Q_OBJECT
    
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
    void onPermissionsChanged();
signals:
    void permissionsChanged();
};

#endif // STAFFRANKMANAGER_H
