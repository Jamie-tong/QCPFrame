QT += widgets

TARGET =  ../../../../bin/Plugins/QPlugin2
TEMPLATE = lib
DEFINES += QPLUGIN2_LIBRARY

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
    pluginform2.cpp \
    wdt_hud.cpp \
    wdt_parampanel.cpp

HEADERS += \
    ../../../interface/coreinterface.h \
    ../../../interface/plugininterface.h \
    PluginIO.h \
    pluginform2.h \
    wdt_hud.h \
    wdt_parampanel.h

DISTFILES +=  \
    QPlugin.json \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    pluginform2.ui \
    wdt_hud.ui \
    wdt_parampanel.ui

RESOURCES += \
    PluginRes.qrc

unix|win32: LIBS += -L$$PWD/../../../bin/ -lQCPF_PluginModel

INCLUDEPATH += $$PWD/../../QCPF_PluginModel
DEPENDPATH += $$PWD/../../QCPF_PluginModel
