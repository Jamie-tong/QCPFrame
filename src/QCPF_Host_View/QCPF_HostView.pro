#-------------------------------------------------
#
# Project created by QtCreator 2019-06-20T17:25:45
#
#-------------------------------------------------

QT       += core gui sql network xml
QT += widgets

TARGET =  ../../../bin/QCPF_HostView

TEMPLATE = app

TRANSLATIONS += English.ts\
                Chinese.ts

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        formloading.cpp \
    initthread.cpp \
        main.cpp \
        mainwindow.cpp \

HEADERS += \
    ../../interface/coreinterface.h \
    ../../interface/plugininterface.h \
        formloading.h \
    initthread.h \
        mainframeinterface.h \
        mainwindow.h \

FORMS += \
        formloading.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../bin/Images/docker.png \
    Core.json

RESOURCES += \
    HostViewRes.qrc


unix|win32: LIBS += -L$$PWD/../../bin/ -lQCPF_Model

INCLUDEPATH += $$PWD/../QCPF_Model
DEPENDPATH += $$PWD/../QCPF_Model

unix|win32: LIBS += -L$$PWD/../../bin/ -lQCPF_ViewModel

INCLUDEPATH += $$PWD/../QCPF_ViewModel
DEPENDPATH += $$PWD/../QCPF_ViewModel

###########################
#                    更新日志
###########################
#【版本】1.0.0.2
#【日期】2022.05.24
#【内容】
# 1. 适配了2.0.0.4版本的QCPF_Model
# 2. 对mainwindow构造函数进行了优化，使OnCoreInitialize在构造最初被调用。
