QT += widgets

win32{
TARGET =  ../../../bin/QCPF_Model
}
unix{
TARGET =  ../../bin/QCPF_Model
}


TEMPLATE = lib
DEFINES += QCPF_MODEL_LIBRARY

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
    configmodel.cpp \
    qcpf_model.cpp

HEADERS += \
    ../../interface/coreinterface.h \
    ../../interface/plugininterface.h \
    configModel.h \
    qcpf_model.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

###########################
#                    更新日志
###########################
#【版本】2.0.0.4
#【日期】2022.05.24
#【内容】
# 1. 优化了整个生命周期内的调用逻辑。
# 2. 优化了插件加载。

#【版本】2.0.0.3
#【日期】2022.05.19
#【内容】
# 1. 增加了基于控制台和基于QMainWindow的Application接口。
# 2. 增加了slot_PreInitialize，用于在Core构造完成就调用插件功能，即提供界面没绘制前的功能调用，而slot_Initialize用于在Loading界面显示时进行的调用。

#【版本】2.0.0.2
#【日期】2022.03.24
#【内容】
# 1. 优化了初始化时多次installConfig导致的问题。
# 2. 优化了InfoType，增加了INFT_EXT_BASE

#【版本】2.0.0.1
#【日期】2021.07.30
#【内容】
# 1. 进一步优化了热拔功能

#【版本】1.0.0.9
#【日期】2021.07.10
#【内容】
# 1. 优化了热插拔功能
# 2. 增加了热插拔配置项，当处于调试状态时，请禁用热插拔，发布时可以开启热插

