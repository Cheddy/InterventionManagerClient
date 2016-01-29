#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Model/Impl/staff.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    
    static Staff user;
    static int serverPort;
    static QString serverAddress;
    static const long long NEW_HOSPITAL_PERMISSION = 1LL << 0;
    static const long long EDIT_HOSPITAL_PERMISSION = 1LL << 1;
    static const long long DELETE_HOSPITAL_PERMISSION = 1LL << 2;
    static const long long NEW_IMPACT_PERMISSION = 1LL << 3;
    static const long long EDIT_IMPACT_PERMISSION = 1LL << 4;
    static const long long DELETE_IMPACT_PERMISSION = 1LL << 5;
    static const long long NEW_PATIENT_PERMISSION = 1LL << 6;
    static const long long EDIT_PATIENT_PERMISSION = 1LL << 7;
    static const long long DELETE_PATIENT_PERMISSION = 1LL << 8;
    static const long long NEW_STAFF_PERMISSION = 1LL << 9;
    static const long long EDIT_STAFF_PERMISSION = 1LL << 10;
    static const long long DELETE_STAFF_PERMISSION = 1LL << 11;
    static const long long NEW_STAFF_RANK_PERMISSION = 1LL << 12;
    static const long long EDIT_STAFF_RANK_PERMISSION = 1LL << 13;
    static const long long DELETE_STAFF_RANK_PERMISSION = 1LL << 14;
    static const long long NEW_WARD_PERMISSION = 1LL << 15;
    static const long long EDIT_WARD_PERMISSION = 1LL << 16;
    static const long long DELETE_WARD_PERMISSION = 1LL << 17;
    static const long long NEW_INTERVENTION_PERMISSION = 1LL << 18;
    static const long long EDIT_INTERVENTION_PERMISSION = 1LL << 19;
    static const long long DELETE_INTERVENTION_PERMISSION = 1LL << 20;
    static const long long NEW_INTERVENTION_DETAIL_PERMISSION = 1LL << 21;
    static const long long EDIT_INTERVENTION_DETAIL_PERMISSION = 1LL << 22;
    static const long long DELETE_INTERVENTION_DETAIL_PERMISSION = 1LL << 23;
    static const long long NEW_INTERVENTION_ACTION_PERMISSION = 1LL << 24;
    static const long long EDIT_INTERVENTION_ACTION_PERMISSION = 1LL << 25;
    static const long long DELETE_INTERVENTION_ACTION_PERMISSION = 1LL << 26;
    static const long long NEW_INTERVENTION_OUTCOME_PERMISSION = 1LL << 27;
    static const long long EDIT_INTERVENTION_OUTCOME_PERMISSION = 1LL << 28;
    static const long long DELETE_INTERVENTION_OUTCOME_PERMISSION = 1LL << 29;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
