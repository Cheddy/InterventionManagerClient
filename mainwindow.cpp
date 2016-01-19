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

Staff MainWindow::user = Staff();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    ui->tabWidget->addTab(new InterventionManager(), "Intervention Manager");     
    ui->tabWidget->addTab(new StaffRankManager(), "Staff Rank Manager"); 
    ui->tabWidget->addTab(new HospitalManager(), "Hospital Manager");     
    ui->tabWidget->addTab(new WardManager(), "Ward Manager");     
    ui->tabWidget->addTab(new PatientManager(), "Patient Manager");         
    ui->tabWidget->addTab(new ImpactManager(), "Impact Manager");      
    ui->tabWidget->addTab(new StaffManager(), "Staff Manager");        
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeTab(int index)
{
    ui->tabWidget->removeTab(index);
}
