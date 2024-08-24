QT       += core gui network sql widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpp/chufanghebingli.cpp \
    cpp/doctoreditpersonalinformation.cpp \
    cpp/editbingli.cpp \
    cpp/guahaoinformation.cpp \
    main.cpp \
    cpp/PatientEditPersonalInformation.cpp \
    cpp/Doctor.cpp \
    cpp/Patient.cpp \
    cpp/mainwindow.cpp \
    cpp/Register.cpp \
    net/ClientSocket.cpp \
    net/NetUtils.cpp \
    net/ServerSocketThread.cpp \
    net/ServerThread.cpp

HEADERS += \
    h/DoctorEditPersonalInformation.h \
    h/chufanghebingli.h \
    h/editbingli.h \
    h/guahaoinformation.h \
    h/PatientEditPersonalInformation.h \
    h/Doctor.h \
    h/mainwindow.h \
    h/Register.h \
    h/Patient.h \
    net/ClientSocket.h \
    net/ServerSocketThread.h \
    net/NetUtils.h \
    net/ServerThread.h \

FORMS += \
    ui/Doctor.ui \
    ui/Patient.ui \
    ui/PatientEditPersonalInformation.ui \
    ui/Doctor-patientCommunicationPlatform.ui \
    ui/DoctorEditPersonalInformation.ui \
    ui/HealthAssesment.ui \
    ui/Register.ui \
    ui/ViewCase.ui \
    ui/ViewDoctorInformations.ui \
    ui/ViewPrescriptionsAndContributions.ui \
    ui/edit_medical_record.ui \
    ui/mainwindow.ui \
    ui/prescription.ui \
    ui/registrationinformation.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    B_I.qrc
