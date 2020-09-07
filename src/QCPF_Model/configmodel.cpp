/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "configmodel.h"

#include <QFile>
#include <QDataStream>


ConfigModel::ConfigModel(QObject* parent){
    this->setParent(parent);
    _this = this;

    resetData();
}

ConfigModel::~ConfigModel(){

}

ConfigModel& ConfigModel::operator = (const ConfigModel& other)
{
    this->_systemName = other._systemName;
    this->_systemID = other._systemID;
    this->_isEnable_UserLoad = other._isEnable_UserLoad;
    this->_count_sysPlugins_Sel = other._count_sysPlugins_Sel;
    this->_count_nSysPlugins_Sel = other._count_nSysPlugins_Sel;
    this->_count_nSysClonePlugins = other._count_nSysClonePlugins;
    this->_count_nSysAllValidPlugins = other._count_nSysAllValidPlugins;

    for(int i=0; i<_count_sysPlugins_Sel; i++)
    {
        this->_sysPlugins_Sel[i]->_pluginID =  other._sysPlugins_Sel[i]->_pluginID;
        this->_sysPlugins_Sel[i]->_pluginFileName =  other._sysPlugins_Sel[i]->_pluginFileName;
    }

    for(int i=0; i<_count_nSysPlugins_Sel; i++)
    {
        this->_nSysPlugins_Sel[i]->_pluginID =  other._nSysPlugins_Sel[i]->_pluginID;
        this->_nSysPlugins_Sel[i]->_pluginFileName =  other._nSysPlugins_Sel[i]->_pluginFileName;
    }

    for(int i=0; i<_count_nSysClonePlugins; i++)
    {
        this->_nSysClonePlugins[i]->_originalPluginID =  other._nSysClonePlugins[i]->_originalPluginID;
        this->_nSysClonePlugins[i]->_copyID =  other._nSysClonePlugins[i]->_copyID;
        this->_nSysClonePlugins[i]->_copyAliasName =  other._nSysClonePlugins[i]->_copyAliasName;
        this->_nSysClonePlugins[i]->_copyComment =  other._nSysClonePlugins[i]->_copyComment;
    }

    for(int i=0; i<_count_nSysAllValidPlugins; i++)
    {
        this-> _nSysAllValidPlugins[i]->_originalPluginID = other._nSysAllValidPlugins[i]->_originalPluginID;
        this-> _nSysAllValidPlugins[i]->_copyID = other._nSysAllValidPlugins[i]->_copyID;
        this-> _nSysAllValidPlugins[i]->_isCopy = other._nSysAllValidPlugins[i]->_isCopy;
    }

    return *this;
}

QDataStream& operator>>(QDataStream& src, ConfigModel& data)
{
    /*
     错误:C2679: 二进制“>>”: 没有找到接受“quint32”类型的右操作数的运算
    解决方法：因为没有添加头文件<QDataStream>
    */
    src >> data._systemName;
    src >> data._systemID;
    src >> data._isEnable_UserLoad;
    src >> data._count_sysPlugins_Sel;
    src >> data._count_nSysPlugins_Sel;
    src >> data._count_nSysClonePlugins;
    src >> data._count_nSysAllValidPlugins;

    for(int i=0; i<data._count_sysPlugins_Sel; i++)
    {
        PluginInfo *tPluginInfo = new PluginInfo(data._this);

        src >> tPluginInfo->_pluginID;
        src >> tPluginInfo->_pluginFileName;

        data._sysPlugins_Sel.append(tPluginInfo);
    }

    for(int i=0; i<data._count_nSysPlugins_Sel; i++)
    {
        PluginInfo *tPluginInfo = new PluginInfo(data._this);

        src >> tPluginInfo->_pluginID;
        src >> tPluginInfo->_pluginFileName;

        data._nSysPlugins_Sel.append(tPluginInfo);
    }

    for(int i=0; i<data._count_nSysClonePlugins; i++)
    {
        ClonePluginInfo *tPluginInfo = new ClonePluginInfo(data._this);

        src >> tPluginInfo->_originalPluginID;
        src >> tPluginInfo->_copyID;
        src >> tPluginInfo->_copyAliasName;
        src >> tPluginInfo->_copyComment;

        data._nSysClonePlugins.append(tPluginInfo);
    }

    for(int i=0; i<data._count_nSysAllValidPlugins; i++)
    {
        ValidPluginInfo *tPluginInfo = new ValidPluginInfo(data._this);

        src >> tPluginInfo->_originalPluginID;
        src >> tPluginInfo->_copyID;
        src >> tPluginInfo->_isCopy;

        data._nSysAllValidPlugins.append(tPluginInfo);
    }
    return src;
}

QDataStream& operator<<(QDataStream& out, ConfigModel& data)
{
    out << data._systemName;
    out << data._systemID;
    out << data._isEnable_UserLoad;
    out << data._count_sysPlugins_Sel;
    out << data._count_nSysPlugins_Sel;
    out << data._count_nSysClonePlugins;
    out << data._count_nSysAllValidPlugins;

    for(int i=0; i<data._count_sysPlugins_Sel; i++)
    {
        out << data._sysPlugins_Sel[i]->_pluginID;
        out << data._sysPlugins_Sel[i]->_pluginFileName;
    }

    for(int i=0; i<data._count_nSysPlugins_Sel; i++)
    {
        out << data._nSysPlugins_Sel[i]->_pluginID;
        out << data._nSysPlugins_Sel[i]->_pluginFileName;
    }

    for(int i=0; i<data._count_nSysClonePlugins; i++)
    {
        out << data._nSysClonePlugins[i]->_originalPluginID;
        out << data._nSysClonePlugins[i]->_copyID;
        out << data._nSysClonePlugins[i]->_copyAliasName;
        out << data._nSysClonePlugins[i]->_copyComment;
    }

    for(int i=0; i<data._count_nSysAllValidPlugins; i++)
    {
        out << data._nSysAllValidPlugins[i]->_originalPluginID;
        out << data._nSysAllValidPlugins[i]->_copyID;
        out << data._nSysAllValidPlugins[i]->_isCopy;
    }

    return out;
}

void ConfigModel::resetData()
{
    _systemName= "";
    _systemID = "";
    _isEnable_UserLoad = false;
    _count_sysPlugins_Sel = 0;
    _count_nSysPlugins_Sel = 0;
    _count_nSysClonePlugins = 0;
    _count_nSysAllValidPlugins = 0;
    _sysPlugins_Sel.clear();
    _nSysPlugins_Sel.clear();
    _nSysClonePlugins.clear();
    _nSysAllValidPlugins.clear();
}

