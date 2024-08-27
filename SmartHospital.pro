QT       += core gui network sql widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpp/ViewRegistration.cpp \
    cpp/usernow.cpp \
    main.cpp \
    cpp/HealthAssesment.cpp \
    cpp/ViewDoctorInformations.cpp \
    cpp/ViewPrescriptionsAndContributions.cpp \
    cpp/ViewCase.cpp \
    cpp/Doctor_patientCommunicationPlatform.cpp \
    cpp/DoctorEditPersonalInformation.cpp \
    cpp/EditRecipeAndPaymentOrder.cpp \
    cpp/EditMedicalRecord.cpp \
    cpp/Registration.cpp \
    cpp/PatientEditPersonalInformation.cpp \
    cpp/Doctor.cpp \
    cpp/Patient.cpp \
    cpp/mainwindow.cpp \
    cpp/Register.cpp \
    cpp/sqliteOperator.cpp \
    net/ClientSocket.cpp \
    net/NetUtils.cpp \
    net/QwenClient.cpp \
    net/ServerSocketThread.cpp \
    net/ServerThread.cpp

HEADERS += \
    h/ViewRegistration.h \
    h/usernow.h \
    h/HealthAssesment.h \
    h/ViewDoctorInformations.h \
    h/ViewPrescriptionsAndContributions.h \
    h/ViewCase.h \
    h/Doctor_patientCommunicationPlatform.h \
    h/DoctorEditPersonalInformation.h \
    h/EditRecipeAndPaymentOrder.h \
    h/EditMedicalRecord.h \
    h/Registration.h \
    h/PatientEditPersonalInformation.h \
    h/Doctor.h \
    h/sqliteOperator.h \
    h/mainwindow.h \
    h/Register.h \
    h/Patient.h \
    net/ClientSocket.h \
    net/QwenClient.h \
    net/ServerSocketThread.h \
    net/NetUtils.h \
    net/ServerThread.h

FORMS += \
    ui/HealthAssesment.ui \
    ui/Register_copy.ui \
    ui/ViewDoctorInformations.ui \
    ui/ViewCase.ui \
    ui/Doctor_patientCommunicationPlatform.ui \
    ui/DoctorEditPersonalInformation.ui \
    ui/Doctor.ui \
    ui/DoctorEditPersonalInformation.ui \
    ui/Doctor_patientCommunicationPlatform.ui \
    ui/EditMedicalRecord.ui \
    ui/Patient.ui \
    ui/PatientEditPersonalInformation.ui \
    ui/EditRecipeAndPaymentOrder.ui \
    ui/HealthAssesment.ui \
    ui/Register.ui \
    ui/Registration.ui \
    ui/ViewCase.ui \
    ui/ViewDoctorInformations.ui \
    ui/ViewPrescriptionsAndContributions.ui \
    ui/ViewRegistration.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    B_I.qrc \
    fin.qrc
