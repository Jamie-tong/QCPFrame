#ifndef QPLUGIN2_H
#define QPLUGIN2_H

#include "qcpf_nonsystempluginmodel.h"

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
    static PluginIO* getInstance();
};

#endif // QPLUGIN2_H
