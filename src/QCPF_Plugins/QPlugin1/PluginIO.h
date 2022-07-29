#ifndef QPLUGIN1_H
#define QPLUGIN1_H

#include "qcpf_nonsystempluginmodel.h"

class PluginIO : public QCPF_NonSystemPluginModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_Interface_iid FILE "QPlugin.json")
    Q_INTERFACES(Plugin_Interface)
public:
    PluginIO();
    ~PluginIO();

    void InitActionList(Plugin_Interface* plugin) Q_DECL_OVERRIDE;
    void InitWidgetList(Plugin_Interface* plugin) Q_DECL_OVERRIDE;

public:
    tagOutputInfo tInfo;

private:
    void Action_SumWidget(bool checkState);
};

#endif // QPLUGIN1_H
