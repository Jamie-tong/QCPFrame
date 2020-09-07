QT -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QCFMANAGER_LIBRARY

TARGET =  ../../../bin/debug/Bin/Plugins/QCPF_ViewEditer
TEMPLATE = lib
CONFIG += plugin

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
    PluginActionViewer.cpp \
    PluginIO.cpp \
    ViewEditer.cpp \
    pluginwidgetviewer.cpp

HEADERS += \
    ../../../interface/hostinterface.h \
    ../../../interface/plugininterface.h \
    PluginActionViewer.h \
    PluginIO.h \
    ViewEditer.h \
    pluginwidgetviewer.h \
    utility/ccheckboxheaderview.h \
    utility/ccheckboxheaderview.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QPlugin.json

FORMS += \
    PluginActionViewer.ui \
    ViewEditer.ui \
    pluginwidgetviewer.ui


unix:!macx|win32: LIBS += -L$$PWD/../../bin/debug/Bin/ -lQCPF_ViewModel

INCLUDEPATH += $$PWD/../../QCPF_ViewModel
DEPENDPATH += $$PWD/../../QCPF_ViewModel
