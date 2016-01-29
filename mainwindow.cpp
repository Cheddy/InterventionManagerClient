#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Managers/Impl/staffrankmanager.h"
#include "Managers/Impl/hospitalmanager.h"
#include "Managers/Impl/wardmanager.h"
#include "Managers/Impl/patientmanager.h"
#include "Managers/Impl/impactmanager.h"
#include "Managers/Impl/staffmanager.h"
#include "Managers/Impl/staffmanager.h"
#include "interventionmanager.h"
#include "Model/Impl/staff.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    long long permissions = MainWindow::user.getRank().getPermissions();
    ui->tabWidget->addTab(new InterventionManager(), "Intervention Manager");  
    
    StaffRankManager *staffRankManager = new StaffRankManager();
    HospitalManager * hospitalManager = new HospitalManager();
    WardManager *wardManager = new WardManager();
    PatientManager *patientManager = new PatientManager();
    ImpactManager *impactManager = new ImpactManager();
    StaffManager *staffManager = new StaffManager();
    
    connect(staffRankManager, &StaffRankManager::permissionsChanged, staffRankManager, &StaffRankManager::onPermissionsChanged);
    connect(staffRankManager, &StaffRankManager::permissionsChanged, hospitalManager, &HospitalManager::onPermissionsChanged);    
    connect(staffRankManager, &StaffRankManager::permissionsChanged, wardManager, &WardManager::onPermissionsChanged);    
    connect(staffRankManager, &StaffRankManager::permissionsChanged, patientManager, &PatientManager::onPermissionsChanged);    
    connect(staffRankManager, &StaffRankManager::permissionsChanged, impactManager, &ImpactManager::onPermissionsChanged);    
    connect(staffRankManager, &StaffRankManager::permissionsChanged, staffManager, &StaffManager::onPermissionsChanged);    
    
    if((permissions & (MainWindow::NEW_STAFF_RANK_PERMISSION | MainWindow::EDIT_STAFF_RANK_PERMISSION | MainWindow::DELETE_STAFF_RANK_PERMISSION)) != 0)    
        ui->tabWidget->addTab(staffRankManager, "Staff Rank Manager"); 
    if((permissions & (MainWindow::NEW_HOSPITAL_PERMISSION | MainWindow::EDIT_HOSPITAL_PERMISSION | MainWindow::DELETE_HOSPITAL_PERMISSION)) != 0)        
        ui->tabWidget->addTab(hospitalManager, "Hospital Manager");   
    if((permissions & (MainWindow::NEW_WARD_PERMISSION | MainWindow::EDIT_WARD_PERMISSION | MainWindow::DELETE_WARD_PERMISSION)) != 0)            
        ui->tabWidget->addTab(wardManager, "Ward Manager");     
    if((permissions & (MainWindow::NEW_PATIENT_PERMISSION | MainWindow::EDIT_PATIENT_PERMISSION | MainWindow::DELETE_PATIENT_PERMISSION)) != 0)                
        ui->tabWidget->addTab(patientManager, "Patient Manager");         
    if((permissions & (MainWindow::NEW_IMPACT_PERMISSION | MainWindow::EDIT_IMPACT_PERMISSION | MainWindow::DELETE_IMPACT_PERMISSION)) != 0)                    
        ui->tabWidget->addTab(impactManager, "Impact Manager");      
    if((permissions & (MainWindow::NEW_STAFF_PERMISSION | MainWindow::EDIT_STAFF_PERMISSION | MainWindow::DELETE_STAFF_PERMISSION)) != 0)                    
        ui->tabWidget->addTab(staffManager, "Staff Manager");  
    
}

MainWindow::~MainWindow()
{
    delete ui;
}
