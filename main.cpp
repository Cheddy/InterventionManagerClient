#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include "Model/Impl/staff.h"
#include <QSettings>

Staff MainWindow::user = Staff();
int MainWindow::serverPort = 8443;
QString MainWindow::serverAddress = "https://localhost";
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    
    
    LoginDialog *loginDialog = new LoginDialog();
    loginDialog->exec();
    delete loginDialog;
    
    MainWindow w;
    w.show();
    
    return a.exec();
}

void loadPropertiesFile(){
    QSettings settings(QString(QApplication::applicationDirPath() + "/properties.ini"), QSettings::IniFormat);
    MainWindow::serverAddress = settings.value("serverAddress", "https://localhost").toString();
    MainWindow::serverPort = settings.value("serverPort", 8443).toInt();    
}
