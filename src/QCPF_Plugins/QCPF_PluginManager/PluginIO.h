/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef QPLUGIN1_H
#define QPLUGIN1_H

#include <QObject>
//包含接口定义
#include "../../../interface/plugininterface.h"
#include "../../../interface/hostinterface.h"
#include "../../QCPF_ViewModel/qcpf_viewmodel.h"

class MyClass
{
public:
    int Var1;
    QString Var2;
    double Var3;
};
Q_DECLARE_METATYPE(MyClass)

class PluginIO : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "QPlugin.json")
    Q_INTERFACES(PluginInterface)
public:
    PluginIO();
    ~PluginIO();
    static PluginIO* getInstance();//静态获取实例

    PluginInterface* Clone(QString copyID, QString copyAliasName, QString copyComments) Q_DECL_OVERRIDE;
    //连接Core，使Plugin获得Core对象实例
    bool ConnectCore(QObject* core) Q_DECL_OVERRIDE;

    int PluginFunction(QVariant arg_in, QVariant &arg_out) Q_DECL_OVERRIDE;

public slots:
    int slot_Plugin(QVariant arg_in, QVariant &arg_out) Q_DECL_OVERRIDE;
    void slot_Action(bool checkState) Q_DECL_OVERRIDE;

    //当core初始化时要执行的过程
    int OnCoreInitialize() Q_DECL_OVERRIDE;
    //当view视图构造完成后，Load前要执行的过程
    int OnViewCreated() Q_DECL_OVERRIDE;
    //当view视图Load时要执行的过程
    int OnViewLoaded() Q_DECL_OVERRIDE;
    //当view视图Closeing时要执行的过程
    int OnViewClosing() Q_DECL_OVERRIDE;

public:
    QCPF_Model *_core;
    tagOutputInfo tinfo;
private:
    void InitActionList(PluginIO* plugin);
    void InitFunctionList(PluginIO* plugin);
    void InitWidgetList(PluginIO* plugin);

    void Action_ShowPluginManager(bool checkState);
};

#endif // QPLUGIN1_H
