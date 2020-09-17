/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef QCPF_MODEL_H
#define QCPF_MODEL_H

#include <QThread>
#include <QDir>
#include "../../interface/hostinterface.h"
#include "../../interface/plugininterface.h"

#include "configModel.h"

#if defined(QCPF_MODEL_LIBRARY)
#  define QCPF_MODEL_EXPORT Q_DECL_EXPORT
#else
#  define QCPF_MODEL_EXPORT Q_DECL_IMPORT
#endif

class QCPF_MODEL_EXPORT QCPF_Model :  public QCPF_Interface
{
        Q_OBJECT
        public:
            QCPF_Model(RunMode runMode, QObject* parent);
            QCPF_Model(RunMode runMode, QObject* parent, QString applicationDirPath, QString sysPluginDirPath, QString nSysPluginDirPath, QString configDirPath, QString configFileName, bool isEnableHotPlug = true);
            ~QCPF_Model();

            ConfigModel _config;
            QObject* _view;
        signals:
            int sig_Core(QVariant arg_in, QVariant &arg_out);//通过该信号与所有组件进行连接
            int sig_OutputInfo(tagOutputInfo& info);//向槽函数发送初始化信息

            void sig_PluginSelOrNSelFinished(QString origPluginID, bool isSel);

            void sig_CloneFinished(bool isExist, QString origPluginID, QString copyID, QString copyAlisaName, QString copyComment);//向槽函数发送克隆组件完成信号
            void sig_DestroyCloneFinished(QString origPluginID, QString copyID);
        private:
            tagOutputInfo _outputInfo;
            int pluginsCollect(bool isCopyToTemp, QString pluginDirPath,  QList<PluginInfo*> selectedPluginInfoList, PluginType type);
            int pluginInstance(QFileInfo fi, PluginType type);
            int installConfig(ConfigModel &config);
            int compareFiles(QString filePath1, QString filePath2);
            int saveConfigFile(QString filePath);

        public slots:
            int slot_Core(QVariant arg_in, QVariant &arg_out);//用于连接所有组件的槽
            int slot_Initialize(QString user, QString pwd, QString extInfo);
            int slot_OutputInfo(tagOutputInfo& info);//接收来自组件的输出信息

            int slot_LoadConfigFile(ConfigModel &config);
            int slot_SaveConfigFile();
            int slot_ApplyConfig();
            int slot_CancelConfig();
};

#endif // QCPF_MODEL_H
