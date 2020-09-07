/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef CONFIGMODEL_H
#define CONFIGMODEL_H

#include <QObject>
#include <QString>
#include "../../interface/hostinterface.h"
#include "../../interface/plugininterface.h"

class PluginInfo:public QObject
{
public:
    QString _pluginID;
    QString _pluginFileName;
public:
    PluginInfo(QObject* parent){this->setParent(parent);}
    PluginInfo(QObject* parent, QString pluginID, QString pluginFileName)
    {
        this->setParent(parent);

        _pluginID = pluginID;
        _pluginFileName = pluginFileName;
    }
};

class ClonePluginInfo:public QObject
{
public:
    QString _originalPluginID;
    QString _copyID;
    QString _copyAliasName;
    QString _copyComment;
public:
    ClonePluginInfo(QObject* parent){this->setParent(parent);}
    ClonePluginInfo(QObject* parent, QString originalPluginID, QString copyID, QString copyAliasName, QString copyComment)
    {
        this->setParent(parent);

        _originalPluginID = originalPluginID;
        _copyID = copyID;
        _copyAliasName = copyAliasName;
        _copyComment = copyComment;
    }
};

class ValidPluginInfo:public QObject
{
public:
    QString _originalPluginID;
    QString _copyID;
    bool _isCopy;
    ValidPluginInfo(QObject* parent){this->setParent(parent);}
    ValidPluginInfo(QObject* parent, QString originalPluginID, QString copyID, bool isCopy)
    {
        this->setParent(parent);

        _originalPluginID = originalPluginID;
        _copyID = copyID;
        _isCopy = isCopy;
    }
};

class ConfigModel:public QObject
{
    Q_OBJECT
public:
    ConfigModel(QObject* parent);
    virtual ~ConfigModel();

    ConfigModel& operator=(const ConfigModel &other);

    friend QDataStream& operator>>(QDataStream&, ConfigModel&);
    friend QDataStream& operator<<(QDataStream&, ConfigModel&);

public://Model相关数据成员
    void resetData();
    ConfigModel* _this;
    QString  _systemName= "通用组件式框架";
    QString _systemID = "GUID";
    bool _isEnable_UserLoad = true;

    int _count_sysPlugins_Sel=0;

    int _count_nSysPlugins_Sel=0;
    int _count_nSysClonePlugins=0;
    int _count_nSysAllValidPlugins=0;

    QList<PluginInfo*> _sysPlugins_Sel;//被选中的系统组件集合

    QList<PluginInfo*> _nSysPlugins_Sel;//被选中的非系统原始组件集合
    QVector<ClonePluginInfo*> _nSysClonePlugins;//克隆非系统组件信息集合
    QVector<ValidPluginInfo*> _nSysAllValidPlugins;//包括原始和克隆组件在内的所有非系统组件加载顺序

    /* 说明：
               1. 系统组件优先与非系统组件被加载
               1. Plugins_Sel Order决定了原始组件文件初次被QPluginLoader创建为实例，即被构造时的先后顺序，而此时克隆组件还未被创建。
               2. ClonePlugins Order决定了第1步以后，克隆组件被克隆的先后顺序。
               3. AllValidPlugins Order决定了接口OnLoading，OnMainFrameCreated，OnMainFrameLoad及OnMainFrameClosing时的先后顺序。
    */
};

#endif // CONFIGMODEL_H
