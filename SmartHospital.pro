QT       += core gui network sql widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpp/chufanghebingli.cpp \
    cpp/editbingli.cpp \
    cpp/guahaoinformation.cpp \
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
    h/chufanghebingli.h \
    h/doctor.h \
    h/editbingli.h \
    h/guahaoInformation.h \
    h/mainwindow.h \
    h/register.h \
    h/patient.h \
    net/NetUtils.h \
    net/ClientSocket.h \
    net/ServerSocketThread.h \
    net/ServerThread.h

FORMS += \
    ui/chufanghebingli.ui \
    ui/editbingli.ui \
    ui/guahaoInformation.ui \
    ui/guahaoInformation.ui \
    ui/patient.ui \
    ui/doctor.ui \
    ui/register.ui \
    ui/mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
