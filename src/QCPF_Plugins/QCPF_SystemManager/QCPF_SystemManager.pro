QT += widgets

DEFINES += QCFMANAGER_LIBRARY

TARGET =  ../../../../bin/Bin/Plugin/QCPF_SystemManager
TEMPLATE = lib
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PluginIO.cpp \
    SystemManager.cpp \
    dialog_about.cpp \
    wdt_coreversion.cpp \
    wdt_currentdatatime.cpp \
    wdt_viewversion.cpp

HEADERS += \
    ../../../interface/coreinterface.h \
    ../../../interface/plugininterface.h \
    PluginIO.h \
    SystemManager.h \
    dialog_about.h \
    utility/ccheckboxheaderview.h \
    wdt_coreversion.h \
    wdt_currentdatatime.h \
    wdt_viewversion.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QPlugin.json

FORMS += \
    SystemManager.ui \
    dialog_about.ui \
    wdt_coreversion.ui \
    wdt_currentdatatime.ui \
    wdt_viewversion.ui


unix|win32: LIBS += -L$$PWD/../../../bin/ -lQCPF_PluginModel

INCLUDEPATH += $$PWD/../../QCPF_PluginModel
DEPENDPATH += $$PWD/../../QCPF_PluginModel

unix|win32: LIBS += -L$$PWD/../../../bin/ -lQCPF_Model

INCLUDEPATH += $$PWD/../../QCPF_Model
DEPENDPATH += $$PWD/../../QCPF_Model

unix|win32: LIBS += -L$$PWD/../../../bin/ -lQCPF_ViewModel

INCLUDEPATH += $$PWD/../../QCPF_ViewModel
DEPENDPATH += $$PWD/../../QCPF_ViewModel

#【版本】1.0.0.4
#【日期】2021.07.10
#【内容】
#1. 优化了热插拔功能
