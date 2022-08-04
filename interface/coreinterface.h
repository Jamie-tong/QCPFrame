/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef MAINFRAMEINTERFACE_H
#define MAINFRAMEINTERFACE_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QQueue>
#include <QThreadPool>
#include <QMutex>
#include <QReadWriteLock>
#include <QSemaphore>
#include <QWaitCondition>

#include "plugininterface.h"

class UserInfo : public QObject
{
public:
    QString _userName = "";
    QString _password = "";
    QString _detail = "";
    QString _createDatetime = "";
    AuthorityType _authority;

    UserInfo()
    {
        _userName = "";
        _password = "";
        _detail = "";
        _createDatetime = "";
        _authority = AT_GUEST;
    }

    UserInfo(QString userName, QString password, QString detail, AuthorityType authority, QString createDatetime)
    {
        _userName = userName;
        _password = password;
        _detail = detail;
        _createDatetime = createDatetime;
        _authority = authority;
    }
};

enum RunMode
{
    RM_CORE_APPLICATION,
    RM_APPLICATION
};

class QCPF_Interface : public QObject
{
        Q_OBJECT
    public:
        RunMode I_RunMode;

        QCoreApplication* I_CoreApplication;
        QApplication* I_Application;
        QList<Plugin_Interface*> I_SysPlugins;
        QList<Plugin_Interface*> I_SysPlugins_Sel;
        QList<Plugin_Interface*> I_SysDiscardedPlugins;
        QList<Plugin_Interface*> I_NSysOrigPlugins;
        QList<Plugin_Interface*> I_NSysOrigPlugins_Sel;
        QList<Plugin_Interface*>  I_NSysClonePlugins;
        QList<Plugin_Interface*> I_NSysAllValidPlugins;
        QList<Plugin_Interface*> I_NSysDiscardedPlugins;

        QString I_SystemID;
        QString I_SystemName;
        QString I_SystemVersion;
        QString I_OrganizationName;
        QString I_ApplicationDirPath;
        QString I_SystemPluginDirPath;
        QString I_NonSysPluginDirPath;
        QString I_ConfigDirPath;
        QString I_ConfigFileName;
        QString I_ConfigFullFilePath;

        QList<UserInfo*> I_UserInfoLst;
        UserInfo I_CurrentUserInfo;
        bool I_EnableLogin;

        bool I_SMBoolVar1;
        bool I_SMBoolVar2;
        int I_SMIntVar1;
        int I_SMIntVar2;
        double I_SMDoubleVar1;
        double I_SMDoubleVar2;
        QString I_SMStrVar1;
        QString I_SMStrVar2;
        QObject I_SMObject1;
        QObject I_SMObject2;
        QList<QObject*> I_SMObjectLst;
        QVector<QObject*> I_SMObjectVec;
        QQueue<QObject*> I_SMObjectQue;
        //Thead
        QThreadPool I_SMThreadPool;
        QThread I_SMThread;
        QMutex I_SMMutex;
        QReadWriteLock I_SMReadWriteLock;
        QSemaphore I_SMSemaphore;
        QWaitCondition I_SMWaitCondition;

signals:
        int sig_OutputInfo(tagOutputInfo& info);
        int sig_Core(QVariant arg_in, QVariant &arg_out);

public slots:
        virtual int slot_InputInfo(tagOutputInfo& info) { return 0; }
        virtual int slot_Core(QVariant arg_in, QVariant &arg_out) { return 0; }

        virtual Plugin_Interface* GetPlugin(PluginType pType, QString pluginID) {return nullptr;};
        virtual PluginActionInfo* GetActionInfo(PluginType pType, QString pluginID, QString actionName) {return nullptr;};
        virtual PluginWidgetInfo* GetWidgetInfo(PluginType pType, QString pluginID, QString widgetName) {return nullptr;};
        virtual PluginFunctionInfo* GetFunctionInfo(PluginType pType, QString pluginID, QString functionName) {return nullptr;};

        virtual Plugin_Interface* GetPlugin_Copy(PluginType pType, QString pluginID, QString copyID) {return nullptr;};
        virtual PluginActionInfo* GetActionInfo_Copy(PluginType pType, QString pluginID, QString copyID, QString actionName) {return nullptr;};
        virtual PluginWidgetInfo* GetWidgetInfo_Copy(PluginType pType, QString pluginID, QString copyID, QString widgetName) {return nullptr;};
        virtual PluginFunctionInfo* GetFunctionInfo_Copy(PluginType pType, QString pluginID, QString copyID, QString functionName) {return nullptr;};

        virtual int Invoke_PluginFunction(PluginType pType, QString pluginID, QString pluginFunctionName) { return 0; }
        virtual int Invoke_PluginFunction(PluginType pType, QString pluginID, QString pluginFunctionName, QVariant arg_in) { return 0; }
        virtual int Invoke_PluginFunction(PluginType pType, QString pluginID, QString pluginFunctionName, QVariant arg_in, QVariant& arg_out) { return 0; }

        virtual int Invoke_PluginFunction_Copy(PluginType pType, QString pluginID, QString copyID, QString pluginFunctionName) { return 0; }
        virtual int Invoke_PluginFunction_Copy(PluginType pType, QString pluginID, QString copyID, QString pluginFunctionName, QVariant arg_in) { return 0; }
        virtual int Invoke_PluginFunction_Copy(PluginType pType, QString pluginID, QString copyID, QString pluginFunctionName, QVariant arg_in, QVariant& arg_out) { return 0; }
};


#define QCPF_Interface_iid "io.qt.interface.qcpfInterface"
Q_DECLARE_INTERFACE(QCPF_Interface, QCPF_Interface_iid)
#endif 
