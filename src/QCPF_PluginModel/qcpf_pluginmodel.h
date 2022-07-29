#ifndef QCPF_PLUGINMODEL_H
#define QCPF_PLUGINMODEL_H

//包含接口定义
#include "../../../interface/plugininterface.h"
#include "../../../interface/coreinterface.h"
#include "../QCPF_Model/qcpf_model.h"

#if defined(QCPF_PLUGINMODEL_LIBRARY)
#  define QCPF_PLUGINMODEL_EXPORT Q_DECL_EXPORT
#else
#  define QCPF_PLUGINMODEL_EXPORT Q_DECL_IMPORT
#endif

class QCPF_PLUGINMODEL_EXPORT QCPF_PluginModel : public Plugin_Interface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_Interface_iid FILE "QPlugin.json")
    Q_INTERFACES(Plugin_Interface)
public:
    QCPF_PluginModel();
    ~QCPF_PluginModel();

    //连接Core，使Plugin获得Core对象实例
    bool ConnectCore(QObject* core) Q_DECL_OVERRIDE;

public slots:
    void slot_Action(bool checkState) Q_DECL_OVERRIDE;

public:
    QCPF_Model* _core;
};





#endif // QCPF_PLUGINMODEL_H
