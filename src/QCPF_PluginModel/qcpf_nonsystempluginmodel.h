#ifndef QCPF_NONSYSTEMPLUGINMODEL_H
#define QCPF_NONSYSTEMPLUGINMODEL_H

#include "qcpf_pluginmodel.h"

class QCPF_PLUGINMODEL_EXPORT QCPF_NonSystemPluginModel : public QCPF_PluginModel
{
    Q_OBJECT
public:
    QCPF_NonSystemPluginModel();
    ~QCPF_NonSystemPluginModel();

    Plugin_Interface* Clone(QString copyID, QString copyAliasName, QString copyComments) Q_DECL_OVERRIDE;
};

#endif //QCPF_NONSYSTEMPLUGINMODEL_H
