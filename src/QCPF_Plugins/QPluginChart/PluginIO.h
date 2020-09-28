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

    void InitWidgetList(Plugin_Interface* plugin) Q_DECL_OVERRIDE;

public:
    QCPF_ViewModel *_view;
    static PluginIO* getInstance();//静态获取实例
};

#endif // QPLUGIN2_H
