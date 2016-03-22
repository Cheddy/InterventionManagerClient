#ifndef WARDMANAGER_H
#define WARDMANAGER_H

#include "Managers/genericmanager.h"

class WardManager : public GenericManager
{
    Q_OBJECT
public:
    WardManager();
    
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

#endif // WARDMANAGER_H
