#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T16:45:27
#
#-------------------------------------------------

QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 

TARGET = InterventionManagerClient
TEMPLATE = app

CONFIG += c++11

RC_FILE = app.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    Managers/genericmanager.cpp \
    Model/datastructure.cpp \
    Model/Impl/staffrank.cpp \
    Network/netutils.cpp \
    Managers/Impl/staffrankmanager.cpp \
    Forms/abstractform.cpp \
    Forms/Impl/staffrankform.cpp \
    Model/Impl/hospital.cpp \
    Managers/Impl/hospitalmanager.cpp \
    Forms/Impl/hospitalform.cpp \
    Model/Impl/ward.cpp \
    Managers/Impl/wardmanager.cpp \
    Forms/Impl/wardform.cpp \
    Components/hospitalcombobox.cpp \
    Model/Impl/patient.cpp \
    Managers/Impl/patientmanager.cpp \
    Forms/Impl/patientform.cpp \
    Model/Impl/impact.cpp \
    Forms/Impl/impactform.cpp \
    Managers/Impl/impactmanager.cpp \
    Components/staffrankcombobox.cpp \
    Model/Impl/staff.cpp \
    Forms/Impl/staffform.cpp \
    Managers/Impl/staffmanager.cpp \
    Model/Impl/interventiondetail.cpp \
    Model/Impl/interventionaction.cpp \
    Forms/Impl/interventionactionform.cpp \
    Managers/Impl/interventionactionmanager.cpp \
    Managers/Impl/interventiondetailmanager.cpp \
    Forms/Impl/interventiondetailform.cpp \
    Model/Impl/interventionoutcome.cpp \
    Managers/Impl/interventionoutcomemanager.cpp \
    Forms/Impl/interventionoutcomeform.cpp \
    Components/impactcombobox.cpp \
    Components/patientcombobox.cpp \
    Components/wardcombobox.cpp \
    Model/Impl/intervention.cpp \
    Forms/interventionform.cpp \
    interventionmanager.cpp \
    logindialog.cpp \
    Forms/Impl/selfeditform.cpp \
    viewdialog.cpp \
    filterselector.cpp \
    Managers/Impl/logmanager.cpp \
    Model/Impl/log.cpp

HEADERS  += mainwindow.h \
    Managers/genericmanager.h \
    Model/datastructure.h \
    Model/Impl/staffrank.h \
    Network/netutils.h \
    Managers/Impl/staffrankmanager.h \
    Forms/abstractform.h \
    Forms/Impl/staffrankform.h \
    Model/Impl/hospital.h \
    Managers/Impl/hospitalmanager.h \
    Forms/Impl/hospitalform.h \
    Model/Impl/ward.h \
    Managers/Impl/wardmanager.h \
    Forms/Impl/wardform.h \
    Components/hospitalcombobox.h \
    Model/Impl/patient.h \
    Managers/Impl/patientmanager.h \
    Forms/Impl/patientform.h \
    Model/Impl/impact.h \
    Forms/Impl/impactform.h \
    Managers/Impl/impactmanager.h \
    Components/staffrankcombobox.h \
    Model/Impl/staff.h \
    Forms/Impl/staffform.h \
    Managers/Impl/staffmanager.h \
    Model/Impl/interventiondetail.h \
    Model/Impl/interventionaction.h \
    Forms/Impl/interventionactionform.h \
    Managers/Impl/interventionactionmanager.h \
    Managers/Impl/interventiondetailmanager.h \
    Forms/Impl/interventiondetailform.h \
    Model/Impl/interventionoutcome.h \
    Managers/Impl/interventionoutcomemanager.h \
    Forms/Impl/interventionoutcomeform.h \
    Components/impactcombobox.h \
    Components/patientcombobox.h \
    Components/wardcombobox.h \
    Model/Impl/intervention.h \
    Forms/interventionform.h \
    interventionmanager.h \
    logindialog.h \
    Forms/Impl/selfeditform.h \
    viewdialog.h \
    filterselector.h \
    Managers/Impl/logmanager.h \
    Model/Impl/log.h

FORMS    += mainwindow.ui \
    Managers/genericmanager.ui \
    Forms/abstractform.ui \
    Components/hospitalcombobox.ui \
    Components/staffrankcombobox.ui \
    Components/impactcombobox.ui \
    Components/patientcombobox.ui \
    Components/wardcombobox.ui \
    Forms/interventionform.ui \
    interventionmanager.ui \
    logindialog.ui \
    viewdialog.ui \
    filterselector.ui
