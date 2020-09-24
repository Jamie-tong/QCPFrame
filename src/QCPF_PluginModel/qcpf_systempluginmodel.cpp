#include "qcpf_systempluginmodel.h"

QCPF_SystemPluginModel::QCPF_SystemPluginModel()
{
    I_PluginType = PT_SYS;
}

QCPF_SystemPluginModel::~QCPF_SystemPluginModel()
{

}

Plugin_Interface* QCPF_SystemPluginModel::Clone(QString copyID, QString copyAliasName, QString copyComment)
{
    return nullptr;
}

