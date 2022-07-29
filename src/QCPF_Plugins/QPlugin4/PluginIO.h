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

public:
    static PluginIO* getInstance();
};

#endif // QPLUGIN2_H
