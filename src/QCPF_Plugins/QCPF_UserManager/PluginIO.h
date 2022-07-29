/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef QPLUGIN1_H
#define QPLUGIN1_H

#include "qcpf_systempluginmodel.h"

class PluginIO : public QCPF_SystemPluginModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_Interface_iid FILE "QPlugin.json")
    Q_INTERFACES(Plugin_Interface)
public:
    PluginIO();
    ~PluginIO();

    void InitActionList(Plugin_Interface* plugin) Q_DECL_OVERRIDE;
    void InitFunctionList(Plugin_Interface* plugin) Q_DECL_OVERRIDE;
    void InitWidgetList(Plugin_Interface* plugin) Q_DECL_OVERRIDE;

public:
    tagOutputInfo tinfo;
    static PluginIO* getInstance();
     int GetUsersInfoFromJson();
private:
    void Action_ShowUserManager(bool checkState);
    int Function_VerifyLoginInfo(QVariant arg_in, QVariant& arg_out);
public slots:

    int OnCoreInitialize() Q_DECL_OVERRIDE;
    int slot_InputInfo(tagOutputInfo& info) Q_DECL_OVERRIDE;
};

#endif // QPLUGIN1_H
