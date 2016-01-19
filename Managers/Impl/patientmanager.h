#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include "Managers/genericmanager.h"

class PatientManager : public GenericManager
{
public:
    PatientManager();
    
public slots:
    void add();    
    void edit();   
    void deleteFunction();    
    void refresh();                
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
    
};

#endif // PATIENTMANAGER_H
