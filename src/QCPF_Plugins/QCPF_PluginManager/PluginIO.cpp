/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "PluginIO.h"

#include <QWidget>
#include <QVariant>
#include <qobject.h>

#include "PluginManager.h"
#include <QStringLiteral>
#include <QAction>
#include <QMessageBox>

PluginIO* instance;
PluginIO::PluginIO()
{
    instance = this;

    I_PluginID = "QCPF_PluginManager";
    I_PluginAliasName = "Plugin Manager";
    I_PluginAuther = "Jamie.T";
    I_PluginVersion = "1.0.0.3";
    I_PluginComment = tr("Manager the Non-system plugins, configure, clone and ordering.");
    I_PluginTag = "SINGLETON\\SYSTEM\\PLUGIN_MANAGER";
    I_PluginAuthority = AT_MANAGER1;
}

PluginIO::~PluginIO(){}

PluginIO* PluginIO::getInstance()
{
    return instance;
}

void PluginIO::InitActionList(Plugin_Interface* plugin)
{
    PluginActionInfo* pai = new PluginActionInfo();
    pai->_actionName = "Plugin Manager";
    pai->_actionDetail = tr("Plugin Manage and sort.");
    pai->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowPluginManager);

    plugin->I_ActionList.append(pai);

}

void PluginIO::InitWidgetList(Plugin_Interface* plugin)
{
    QCPF_Model* core = (QCPF_Model*)_core;
    PluginWidgetInfo *nFormInfo = new PluginWidgetInfo();

    nFormInfo->_showType = ST_POPUP;
    nFormInfo->_widget = new PluginManager(core);
    nFormInfo->_widget->setObjectName("wdt_PluginManager");
    nFormInfo->_origWidth = nFormInfo->_widget->width();
    nFormInfo->_origHeight = nFormInfo->_widget->height();
    nFormInfo->_widgetDetail = tr("It's used for managing the Non-System plugins");

    plugin->I_WidgetList.append(nFormInfo);
}

int PluginIO::slot_InputInfo(tagOutputInfo& info)
{
    if(info._type == INFT_PLUGIN_COLLECT_FINISHED)
    {
        PluginManager::getInstance()->setConfigToUI();
    }

    return 0;
}

void PluginIO::Action_ShowPluginManager(bool checkState)
{
    QAction* actSender = (QAction*)sender();
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == QStringLiteral("wdt_PluginManager"))
            {
                pwi->_widget->setWindowIcon(actSender->icon());
                ((QDialog*)pwi->_widget)->exec();
            }
        }
    }
}
