#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Managers/Impl/staffrankmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    ui->tabWidget->addTab(new StaffRankManager(), "Staff Rank Manager"); 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeTab(int index)
{
    ui->tabWidget->removeTab(index);
}
