QT += widgets

TEMPLATE = lib
DEFINES += QCPF_PLUGINMODEL_LIBRARY

TARGET =  ../../../bin/QCPF_PluginModel

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
    qcpf_nonsystempluginmodel.cpp \
    qcpf_pluginmodel.cpp \
    qcpf_systempluginmodel.cpp

HEADERS += \
    ../../interface/coreinterface.h \
    ../../interface/plugininterface.h \
    qcpf_nonsystempluginmodel.h \
    qcpf_pluginmodel.h \
    qcpf_systempluginmodel.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


unix|win32: LIBS += -L$$PWD/../../bin/ -lQCPF_Model

INCLUDEPATH += $$PWD/../QCPF_Model
DEPENDPATH += $$PWD/../QCPF_Model
