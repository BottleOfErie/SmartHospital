QT       += core gui network sql widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    cpp/doctor.cpp \
    cpp/patient.cpp \
    cpp/mainwindow.cpp \
    cpp/register.cpp \
    net/ClientSocket.cpp \
    net/NetUtils.cpp \
    net/ServerSocketThread.cpp \
    net/ServerThread.cpp

HEADERS += \
    h/doctor.h \
    h/mainwindow.h \
    net/ClientSocket.h \
    net/ServerSocketThread.h \
    net/NetUtils.h \
    net/ServerThread.h \
    h/register.h \
    h/patient.h

FORMS += \
    ui/Check_the_registration.ui \
    ui/Doctor-patientCommunicationPlatform.ui \
    ui/Doctor.ui \
    ui/DoctorEditPersonalInformation.ui \
    ui/HealthAssesment.ui \
    ui/Patient.ui \
    ui/PatientEditPersonalInformation.ui \
    ui/Register.ui \
    ui/ViewCase.ui \
    ui/ViewDoctorInformations.ui \
    ui/ViewPrescriptionsAndContributions.ui \
    ui/mainwindow.ui \
    ui/zhuce.ui \
    ui/register.ui \
    ui/mainwindow.ui \
    ui/编辑处方和缴费单.ui \
    ui/编辑病例.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    B_I.qrc
