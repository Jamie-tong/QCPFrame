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

#include "ViewEditor.h"
#include <QStringLiteral>
#include <QAction>

PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;
    PluginIO::I_PluginID = tr("QCPF_ViewEditor");
    PluginIO::I_PluginType = PT_SYS;
    PluginIO::I_PluginAliasName = tr("View Editor");
    PluginIO::I_PluginAuther = tr("Jamie.T");
    PluginIO::I_PluginVersion = tr("1.0.0.1");
    PluginIO::I_PluginComment = tr("Edit the view of main window, such as menu-bar, tool-bar, status-bar and workspace.");
    PluginIO::I_PluginTag = tr("SINGLETON\\SYSTEM\\VIEW_EDITER");
    PluginIO::I_PluginAuthority = AT_DEVELOPER1;

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
    //--------------------------------------------
    PluginActionInfo* pai1 = new PluginActionInfo();
    pai1->_actionName = tr("View editor");
    pai1->_actionDetail = tr("It's used for editing menubar,toolbar,statusbar,workspace and any other ui elements of main appliction frame.");
    pai1->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowViewEditor);

    plugin->I_ActionList.append(pai1);
}

void PluginIO::InitFunctionList(PluginIO* plugin)
{

}

void PluginIO::InitWidgetList(PluginIO* plugin)
{
    PluginWidgetInfo *nWdtViewEditor = new PluginWidgetInfo();

    nWdtViewEditor->_showType = ST_POPUP;
    nWdtViewEditor->_widget = new ViewEditor();
    nWdtViewEditor->_widget->setObjectName(QStringLiteral("wdt_ViewEditor"));
    nWdtViewEditor->_origWidth = nWdtViewEditor->_widget->width();
    nWdtViewEditor->_origWidth = nWdtViewEditor->_widget->height();
    nWdtViewEditor->_widgetDetail = tr("It's used for editing the view that refer to menu,toolbar,worke eara and status bar.");

    plugin->I_WidgetList.append(nWdtViewEditor);
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
void PluginIO::Action_ShowViewEditor(bool checkState)
{
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == QStringLiteral("wdt_ViewEditor"))
            {
                ((QDialog*)pwi->_widget)->exec();
            }
        }
    }
}

