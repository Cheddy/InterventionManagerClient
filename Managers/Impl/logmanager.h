#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include "Managers/genericmanager.h"

class LogManager : public GenericManager
{
    Q_OBJECT
public:
    LogManager();
    
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

#endif // LOGMANAGER_H
