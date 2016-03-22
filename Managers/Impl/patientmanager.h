#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include "Managers/genericmanager.h"

class PatientManager : public GenericManager
{
    Q_OBJECT
public:
    PatientManager();
    
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

#endif // PATIENTMANAGER_H
