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
#include "../../interface/coreinterface.h"
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

public:
    void resetData();
    ConfigModel* _this;
    QString  _systemName= "通用组件式框架";
    QString _systemID = "GUID";
    bool _isEnable_UserLoad = true;

    int _count_sysPlugins_Sel=0;

    int _count_nSysPlugins_Sel=0;
    int _count_nSysClonePlugins=0;
    int _count_nSysAllValidPlugins=0;

    QList<PluginInfo*> _sysPlugins_Sel;

    QList<PluginInfo*> _nSysPlugins_Sel;
    QVector<ClonePluginInfo*> _nSysClonePlugins;
    QVector<ValidPluginInfo*> _nSysAllValidPlugins;
};

#endif // CONFIGMODEL_H
