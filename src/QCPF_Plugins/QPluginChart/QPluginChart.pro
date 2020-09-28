QT += widgets
QT += charts
QT += multimedia

TARGET =  ../../../../bin/Plugins/QPluginChart
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
    chart.cpp \
    chartview.cpp \
    wdt_areachart.cpp \
    wdt_audio.cpp \
    wdt_zoomchart.cpp \
    widget.cpp \
    xyseriesiodevice.cpp

HEADERS += \
    PluginIO.h \
    chart.h \
    chartview.h \
    wdt_areachart.h \
    wdt_audio.h \
    wdt_zoomchart.h \
    widget.h \
    xyseriesiodevice.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/../../../bin/ -lQCPF_PluginModel

INCLUDEPATH += $$PWD/../../QCPF_PluginModel
DEPENDPATH += $$PWD/../../QCPF_PluginModel

FORMS += \
    wdt_areachart.ui \
    wdt_audio.ui \
    wdt_zoomchart.ui
