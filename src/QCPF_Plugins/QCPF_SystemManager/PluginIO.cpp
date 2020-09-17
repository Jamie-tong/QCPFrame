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

PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;
    PluginIO::I_PluginID = tr("QCPF_SystemManager");
    PluginIO::I_PluginType = PT_SYS;
    PluginIO::I_PluginAliasName = tr("System Manager");
    PluginIO::I_PluginAuther = tr("Jamie.T");
    PluginIO::I_PluginVersion = tr("1.0.0.1");
    PluginIO::I_PluginComment = tr("Manage the system params.");
    PluginIO::I_PluginTag = tr("SINGLETON\\SYSTEM\\SYS_PLUGIN_MANAGER");
    PluginIO::I_PluginAuthority = AT_MANAGER1;

    PluginIO::I_IsCopy = false;
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
PluginInterface* PluginIO::Clone(QString copyID, QString copyAliasName, QString copyComment)
{
    return nullptr;
}

bool PluginIO::ConnectCore(QObject* core){

    _core = (QCPF_Model*)(core);
    InitActionList(this);
    InitFunctionList(this);
    if(_core->I_RunMode == RM_APPLICATION)
            InitWidgetList(this);

    return _core?true:false;
}

void PluginIO::slot_Action(bool checkState){
    QAction *action = (QAction*)sender();
    QString actionName =  action->property("ItemActionName").toString();

    foreach (PluginActionInfo* pai, I_ActionList) {
        if(pai->_actionName == action->text() || pai->_actionName == actionName)
        {
            (this->*pai->_pAction)(checkState);
            break;
        }
    }
}

void PluginIO::InitActionList(PluginIO* plugin)
{
    PluginActionInfo* pai = new PluginActionInfo();
    pai->_actionName = tr("System Manager");
    pai->_actionDetail = tr("Manage the system module and params.");
    pai->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowSystemPluginManager);

    plugin->I_ActionList.append(pai);

    PluginActionInfo* pai2 = new PluginActionInfo();
    pai2->_actionName = tr("Plugin Route Editer.");
    pai2->_actionDetail = tr("config the connect route in plugin functions");
    pai2->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowRouteManager);

    plugin->I_ActionList.append(pai2);

    PluginActionInfo* pai3 = new PluginActionInfo();
    pai3->_actionName = tr("Exit");
    pai3->_actionDetail = tr("Exit and close the main application.");
    pai3->_pAction = (FPTR_ACTION)(&PluginIO::Action_CloseMainApplication);

    plugin->I_ActionList.append(pai3);

    PluginActionInfo* pai4 = new PluginActionInfo();
    pai4->_actionName = tr("About");
    pai4->_actionDetail = tr("show about form.");
    pai4->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowAboutForm);

    plugin->I_ActionList.append(pai4);
}

void PluginIO::InitFunctionList(PluginIO* plugin)
{

}

void PluginIO::InitWidgetList(PluginIO* plugin)
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
    nWdtAbout->_widgetDetail = tr("It's used for introducing QCommonFrame.");

    plugin->I_WidgetList.append(nWdtAbout);
}

//通用方法
int PluginIO::PluginFunction(QVariant arg_in, QVariant &arg_out){

//    QVariant tt("12315");
    MyClass ms;
    ms.Var1 = 1;
    ms.Var2 = "123";
    ms.Var3 = 3.4;
    QVariant vms;
    vms.setValue(ms);
    arg_out = vms;
    return 111;
}

//-----------------------------------
//通用槽函数
int PluginIO::slot_Plugin(QVariant arg_in, QVariant &arg_out) {

return 0;
}

int PluginIO::OnCoreInitialize(){

    return 0;
}

int PluginIO::OnViewCreated(){

    return 0;
}

int PluginIO::OnViewLoaded(){

    return 0;
}

int PluginIO::OnViewClosing(){

    return 0;
}

/***********************************************************************
 *  action 函数指针所对应的回调函数
 * *********************************************************************/
void PluginIO::Action_ShowSystemPluginManager(bool checkState)
{
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == "wdt_SystemPluginManager")
            {
                ((QDialog*)pwi->_widget)->exec();
            }
        }
    }
}

void PluginIO::Action_ShowRouteManager(bool checkState)
{
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == "wdt_RouteManager")
            {
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
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == "Dialog_About")
            {
                ((QDialog*)pwi->_widget)->exec();
            }
        }
    }
}
