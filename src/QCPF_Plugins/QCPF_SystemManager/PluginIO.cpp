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

#include "SystemManager.h"
#include <QStringLiteral>
#include <QAction>

#include "wdt_currentdatatime.h"
#include "dialog_about.h"
#include "wdt_coreversion.h"
#include "wdt_viewversion.h"
#include <QMessageBox>

PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;

    I_PluginID = tr("QCPF_SystemManager");
    I_PluginAliasName = tr("System Manager");
    I_PluginAuther = tr("Jamie.T");
    I_PluginVersion = tr("1.0.0.2");
    I_PluginComment = tr("Manage the system params.");
    I_PluginTag = tr("SINGLETON\\SYSTEM\\SYS_PLUGIN_MANAGER");
    I_PluginAuthority = AT_MANAGER1;
}

PluginIO::~PluginIO(){}

PluginIO* PluginIO::getInstance()
{
    return instance;
}

//接口方法实现
/***************************************************
*                       方法接口                                       *
***************************************************/
void PluginIO::InitActionList(Plugin_Interface* plugin)
{
    PluginActionInfo* paiSysMgr = new PluginActionInfo();
    paiSysMgr->_actionName = tr("System Manager");
    paiSysMgr->_actionDetail = tr("Manage the system module and params.");
    paiSysMgr->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowSystemPluginManager);

    plugin->I_ActionList.append(paiSysMgr);

    PluginActionInfo* paiExit = new PluginActionInfo();
    paiExit->_actionName = tr("Exit");
    paiExit->_actionDetail = tr("Exit and close the main application.");
    paiExit->_pAction = (FPTR_ACTION)(&PluginIO::Action_CloseMainApplication);

    plugin->I_ActionList.append(paiExit);

    PluginActionInfo* paiAbout = new PluginActionInfo();
    paiAbout->_actionName = tr("About");
    paiAbout->_actionDetail = tr("show about form.");
    paiAbout->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowAboutForm);

    plugin->I_ActionList.append(paiAbout);
}

void PluginIO::InitWidgetList(Plugin_Interface* plugin)
{
    QCPF_Model* core = (QCPF_Model*)_core;
    PluginWidgetInfo *nWdtPluginManager = new PluginWidgetInfo();

    nWdtPluginManager->_showType = ST_POPUP;
    nWdtPluginManager->_widget = new SystemManager(core);
    nWdtPluginManager->_widget->setObjectName("wdt_SystemPluginManager");
    nWdtPluginManager->_origWidth = nWdtPluginManager->_widget->width();
    nWdtPluginManager->_origHeight = nWdtPluginManager->_widget->height();
    nWdtPluginManager->_widgetDetail = tr("It's used for managing the System plugins.");
    plugin->I_WidgetList.append(nWdtPluginManager);
    //-------------------
    PluginWidgetInfo *nWdtCurrentDateTime = new PluginWidgetInfo();

    nWdtCurrentDateTime->_showType = ST_DOCK;
    nWdtCurrentDateTime->_widget = new wdt_CurrentDataTime();
    nWdtCurrentDateTime->_origWidth = nWdtCurrentDateTime->_widget->width();
    nWdtCurrentDateTime->_origHeight = nWdtCurrentDateTime->_widget->height();
    nWdtCurrentDateTime->_widgetDetail = tr("It's used for showwing the data time.");

    plugin->I_WidgetList.append(nWdtCurrentDateTime);
    //-------------------
    PluginWidgetInfo *nWdtAbout = new PluginWidgetInfo();

    nWdtAbout->_showType = ST_POPUP;
    nWdtAbout->_widget = new Dialog_About();
    nWdtAbout->_origWidth = nWdtAbout->_widget->width();
    nWdtAbout->_origHeight = nWdtAbout->_widget->height();
    nWdtAbout->_widgetDetail = tr("It's used for introducing QCPFrame.");

    plugin->I_WidgetList.append(nWdtAbout);

    //-------------------
    PluginWidgetInfo *nWdt_CoreVer = new PluginWidgetInfo();

    nWdt_CoreVer->_showType = ST_DOCK;
    nWdt_CoreVer->_widget = new wdt_CoreVersion();
    nWdt_CoreVer->_origWidth = nWdt_CoreVer->_widget->width();
    nWdt_CoreVer->_origHeight = nWdt_CoreVer->_widget->height();
    nWdt_CoreVer->_widgetDetail = tr("Show core version.");

    plugin->I_WidgetList.append(nWdt_CoreVer);

    //-------------------
    PluginWidgetInfo *nWdt_ViewVer = new PluginWidgetInfo();

    nWdt_ViewVer->_showType = ST_DOCK;
    nWdt_ViewVer->_widget = new wdt_ViewVersion();
    nWdt_ViewVer->_origWidth = nWdt_ViewVer->_widget->width();
    nWdt_ViewVer->_origHeight = nWdt_ViewVer->_widget->height();
    nWdt_ViewVer->_widgetDetail = tr("Show view model version.");

    connect(this, SIGNAL(StartShowViewVersion(void)), nWdt_ViewVer->_widget , SLOT(ShowViewVersion(void)));
    bool ret = disconnect(this, SIGNAL(StartShowViewVersion(void)), nWdt_ViewVer->_widget , SLOT(ShowViewVersion(void)));
    plugin->I_WidgetList.append(nWdt_ViewVer);
}

int PluginIO::slot_InputInfo(tagOutputInfo& info)
{
    if(info._type == INFT_PLUGIN_COLLECT_FINISHED)
        SystemManager::getInstance()->setConfigToUI();
//    else if(info._type == INFT_CORE_CONFIG_CHANGED)
//    {
//        if(SystemManager::getInstance()!=nullptr)
//        {
//            QMessageBox::information(SystemManager::getInstance(), tr("information"), tr("System configuration has changed, please restart application for updating."));
//            SystemManager::getInstance()->close();
//        }
//    }

    return 0;
}

/***********************************************************************
 *  action 函数指针所对应的回调函数
 * *********************************************************************/
void PluginIO::Action_ShowSystemPluginManager(bool checkState)
{
    QAction* actSender = (QAction*)sender();
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == "wdt_SystemPluginManager")
            {
                pwi->_widget->setWindowIcon(actSender->icon());
                ((QDialog*)pwi->_widget)->exec();
            }
        }
    }
}

void PluginIO::Action_CloseMainApplication(bool checkState)
{
    tagOutputInfo tInfo;
    tInfo._type = INFT_APPLICATION_CLOSE;
    sig_OutputInfo(tInfo);
}

void PluginIO::Action_ShowAboutForm(bool checkState)
{
    QAction* actSender = (QAction*)sender();
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == "Dialog_About")
            {
                pwi->_widget->setWindowIcon(actSender->icon());
                ((QDialog*)pwi->_widget)->exec();
            }
        }
    }
}
