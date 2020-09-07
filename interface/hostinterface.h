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
#include<QQueue>

#include "plugininterface.h"

class UserInfo : public QObject
{
public:
    QString _userName = "";
    QString _password = "";
    AuthorityType _authority;

    UserInfo()
    {
        _userName = "";
        _password = "";
        _authority = AT_GUEST;
    }

    UserInfo(QString userName, QString password, AuthorityType authority)
    {
        _userName = userName;
        _password = password;
        _authority = authority;
    }
};

class QCPF_Interface : public QObject
{
        Q_OBJECT
    public:
        /**********************************************************************************
         * 系统组件:
         *     1. 用以扩展系统功能，在加载时，首先被加载，其余Plugins为非系统组件。
         *     2. 系统组件可以选择哪些可用哪些不可用，这可以用于用户权限管理等功能
         *     3. 系统为单例组件，可排序，但是不容许被克隆。
         **********************************************************************************/
        //所有系统组件集合
        QList<PluginInterface*> I_SysPlugins;
        //所有被选中的系统组件集合
        QList<PluginInterface*> I_SysPlugins_Sel;

        /**********************************************************************************
         * 非系统组件:
         *     1. 用以实现业务层功能，在系统组件加载完成过后被加载。
         *     2. 非系统组件可以选择哪些可用哪些不可用，这可以用于用户权限管理等功能
         *     3. 非系统组件可排序，可以被克隆。
         **********************************************************************************/
        //非系统原始组件集合
        QList<PluginInterface*> I_NSysOrigPlugins;
        //被选中的非系统原始组件集合
        QList<PluginInterface*> I_NSysOrigPlugins_Sel;
        //克隆组件集合，克隆组件必须是从I_NSysOrigPlugins_Sel中生成的副本
        QList<PluginInterface*>  I_NSysClonePlugins;
        //包括已选择的原始组件和克隆组件在内的所有非系统组件的集合
        QList<PluginInterface*> I_NSysAllValidPlugins;
        //=====================当前配置文件目录和组件目录
        QString I_SystemID;
        QString I_SystemName;
        QString I_ApplicationDirPath;
        QString I_SystemPluginDirPath;
        QString I_NonSysPluginDirPath;
        QString I_ConfigDirPath;
        QString I_ConfigFileName;
        QString I_ConfigFullFilePath;
        bool I_IsEnableHotPlug;
        //================================================Users
        //用户信息
        QList<UserInfo*> I_UserInfoLst;
        UserInfo I_CurrentUserInfo;
        //================================================SharedMemory
        //组件间共享内存
        bool I_SMBoolVar1;
        bool I_SMBoolVar2;
        int I_SMIntVar1;
        int I_SMIntVar2;
        double I_SMDoubleVar1;
        double I_SMDoubleVar2;
        QString I_SMStrVar1;
        QString I_SMStrVar2;
        QObject* I_SMObject1;
        QObject* I_SMObject2;
        QList<QObject*> I_SMObjectLst;
        QVector<QObject*> I_SMObjectVec;
        QQueue<QObject*> I_SMObjectQue;

signals:
        int HostSignal_OnLoading();
        int HostSignal_OnMainFrameCreated();
        int HostSignal_OnMainFrameLoad();
        int HostSignal_OnMainFrameClose();
};

//这个宏将一个给定的字符串标识符和ClassName所表示的接口相关联，其中Identifier必须唯一。
#define QCPF_Interface_iid "io.qt.interface.qcpfInterface"
Q_DECLARE_INTERFACE(QCPF_Interface, QCPF_Interface_iid)
#endif // MAINFRAMEINTERFACE_H
