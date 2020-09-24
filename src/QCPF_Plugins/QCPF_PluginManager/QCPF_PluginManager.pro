QT += widgets

DEFINES += QCFMANAGER_LIBRARY

TARGET =  ../../../../bin/Bin/Plugins/QCPF_PluginManager
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
    PluginManager.cpp

HEADERS += \
    ../../../interface/coreinterface.h \
    ../../../interface/plugininterface.h \
    PluginIO.h \
    PluginManager.h \
    utility/ccheckboxheaderview.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QPlugin.json

FORMS += \
    PluginManager.ui

unix|win32: LIBS += -L$$PWD/../../../bin/ -lQCPF_PluginModel

INCLUDEPATH += $$PWD/../../QCPF_PluginModel
DEPENDPATH += $$PWD/../../QCPF_PluginModel
