#ifndef INTERVENTIONOUTCOMEMANAGER_H
#define INTERVENTIONOUTCOMEMANAGER_H

#include "Managers/genericmanager.h"
#include <QList>
#include "Model/Impl/interventionoutcome.h"

class InterventionOutcomeManager : public GenericManager
{
    Q_OBJECT
public:
    InterventionOutcomeManager();
    
public slots:
    void add();    
    void edit();   
    void deleteFunction();    
    void refresh();   
    void add(QList<InterventionOutcome> list);
    QList<InterventionOutcome> get();        
    void onAdd(DataStructure *structure);
    void onEdit(DataStructure *structure);
    void onDelete(DataStructure *structure);
    void onPermissionsChanged();
    
};

#endif // INTERVENTIONOUTCOMEMANAGER_H
