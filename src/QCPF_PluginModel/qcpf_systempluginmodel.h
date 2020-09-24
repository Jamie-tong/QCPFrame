#ifndef QCPF_SYSTEMPLUGINMODEL_H
#define QCPF_SYSTEMPLUGINMODEL_H

#include "qcpf_pluginmodel.h"

class QCPF_PLUGINMODEL_EXPORT QCPF_SystemPluginModel : public QCPF_PluginModel
{
    Q_OBJECT
public:
    QCPF_SystemPluginModel();
    ~QCPF_SystemPluginModel();

    Plugin_Interface* Clone(QString copyID, QString copyAliasName, QString copyComments) Q_DECL_OVERRIDE;
};

#endif // QCPF_SYSTEMPLUGINMODEL_H
