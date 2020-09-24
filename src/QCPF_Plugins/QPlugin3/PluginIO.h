#ifndef QPLUGIN2_H
#define QPLUGIN2_H

#include "../../QCPF_PluginModel/qcpf_nonsystempluginmodel.h"

class PluginIO : public QCPF_NonSystemPluginModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_Interface_iid FILE "QPlugin.json")
    Q_INTERFACES(Plugin_Interface)
public:
    PluginIO();
    ~PluginIO();

    void InitActionList(Plugin_Interface* plugin)  Q_DECL_OVERRIDE;
    void InitFunctionList(Plugin_Interface* plugin)  Q_DECL_OVERRIDE;

public:
    static PluginIO* getInstance();//静态获取实例
//==============================================
public:
    void Action_sum(bool checkState);

    int Function_StepUp(QVariant arg_in, QVariant& arg_out);
    int Function_StepDown(QVariant arg_in, QVariant& arg_out);

    int Function_StepStartTimer(QVariant arg_in, QVariant& arg_out);
    int Function_StepStopTimer(QVariant arg_in, QVariant& arg_out);

    int Function_StepThread(QVariant arg_in, QVariant& arg_out);
public slots:
    void handleTimeout(); //超时处理函数
};

#endif // QPLUGIN2_H
