QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    cpp/mainwindow.cpp \
    net/ClientSocket.cpp \
    net/ServerSocketThread.cpp \
    net/ServerThread.cpp

HEADERS += \
    h/mainwindow.h \
    net/ClientSocket.h \
    net/ServerSocketThread.h \
    net/NetUtils.h \
    net/ServerThread.h

FORMS += \
    ui/mainwindow.ui \
    ui/yisheng.ui \
    ui/zhuce.ui \
    ui/查看挂号信息.ui \
    ui/编辑处方和缴费单.ui \
    ui/编辑病例.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
