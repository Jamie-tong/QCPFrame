#include "QCPF_Controllor.h"
#include <QCoreApplication.h>
#include <QDebug>
#include <QVariant>

#include <iostream>
using namespace std;

QCPF_Controllor::QCPF_Controllor()
{
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString sysPluginDirPath = appDirPath + "/Bin/Plugins/";
    QString nSyspluginDirPath = appDirPath + "/Plugins/";

    QString _coreConfigFileDirPath = appDirPath + "/Config/Core/";
    QString _coreConfigFileName = "CoreConfig.dat";

    QString _viewConfigFileDirPath = appDirPath + "/Config/View/";
    QString _viewConfigFileName = "ViewConfig.dat";

    //create core object
    _core = new QCPF_Model(RM_CORE_APPLICATION, this, appDirPath, sysPluginDirPath, nSyspluginDirPath, _coreConfigFileDirPath, _coreConfigFileName);

    connect(_core, SIGNAL(sig_OutputInfo(tagOutputInfo&)), this, SLOT(slot_CoreInfo(tagOutputInfo&)));
}

int QCPF_Controllor::slot_CoreInfo(tagOutputInfo& info)
{
    switch (info._type) {

            case InfoType::INFT_STATUS_INFO:
                    qDebug() << info._content;
            break;
        }

       return 0;
}

void QCPF_Controllor::GetCoreInfo(QString& systemName, QString& systemID, QString& systemVersion, QString& organizetionName)
{
    systemName = _core->I_SystemName;
    systemID = _core->I_SystemID;
    systemVersion = _core->I_SystemVersion;
    organizetionName = _core->I_OrganizationName;
}

void QCPF_Controllor::PluginCollect()
{
    _core->slot_Initialize("tt", "1", "");
}

void QCPF_Controllor::GetPluginIDList()
{
    PluginCollect();

    qDebug() <<tr("======================System Plugins======================");
    foreach (PluginInterface* pi, _core->I_SysPlugins) {
        qDebug() << pi->I_PluginID;
    }

    qDebug() <<tr("=====================Non-System Plugins======================");
    foreach (PluginInterface* pi, _core->I_NSysOrigPlugins) {
        qDebug() << pi->I_PluginID;
    }
}

void QCPF_Controllor::GetFunctionListFromPlugin(QString pluginID)
{
    PluginCollect();

    qDebug() <<"";
    foreach (PluginInterface* pi, _core->I_NSysOrigPlugins) {
        if(pluginID == pi->I_PluginID)
        {
            foreach(PluginFunctionInfo* pfi, pi->I_FunctionList)
            {
                qDebug() <<"[Function]:"<< pfi->_functionName<<"  [Detail]:" << pfi->_functionDetail;
            }
            break;
        }
    }
}

void QCPF_Controllor::PerformFunction(QString pluginID, QString copyID, QString functionName)
{
    PluginCollect();

    qDebug() <<"";
    foreach (PluginInterface* pi, _core->I_NSysAllValidPlugins) {

        if(0==pluginID.compare(pi->I_PluginID) && 0==copyID.compare(pi->I_CopyID))
        {
            foreach(PluginFunctionInfo* pfi, pi->I_FunctionList)
            {
                if(functionName == pfi->_functionName)
                {
                    QVariant v1;
                    QVariant v2 = false;
                    int ret = (pi->*pfi->_pFunction)(v1, v2);
                    break;
                }
            }
            break;
        }
    }
}
