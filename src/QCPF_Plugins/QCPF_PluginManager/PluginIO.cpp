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

PluginIO* instance;
PluginIO::PluginIO()
{
    instance = this;

    PluginIO::I_PluginID = tr("QCPF_PluginManager");
    PluginIO::I_PluginType = PT_SYS;
    PluginIO::I_PluginAliasName = tr("Plugin Manager");
    PluginIO::I_PluginAuther = tr("Jamie.T");
    PluginIO::I_PluginVersion = tr("1.0.0.1");
    PluginIO::I_PluginComment = tr("Manager the Non-system plugins, configure, clone and ordering.");
    PluginIO::I_PluginTag = tr("SINGLETON\\SYSTEM\\PLUGIN_MANAGER");
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
    pai->_actionName = tr("Plugin Manager");
    pai->_actionDetail = tr("Plugin Manage and sort.");
    pai->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowPluginManager);

    plugin->I_ActionList.append(pai);

}

void PluginIO::InitFunctionList(PluginIO* plugin)
{

}

void PluginIO::InitWidgetList(PluginIO* plugin)
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

//通用方法
int PluginIO::PluginFunction(QVariant arg_in, QVariant &arg_out){
    return 0;
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
void PluginIO::Action_ShowPluginManager(bool checkState)
{
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == QStringLiteral("wdt_PluginManager"))
            {
                ((QDialog*)pwi->_widget)->exec();
            }
        }
    }
}
