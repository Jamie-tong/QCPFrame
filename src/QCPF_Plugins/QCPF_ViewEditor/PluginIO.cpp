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
    PluginIO::I_PluginID = tr("QCFViewEditor");
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
    PluginIO *_clonePlugin = new PluginIO();

    _clonePlugin->I_PluginID = this->I_PluginID;
    _clonePlugin->I_PluginType = this->I_PluginType;
    _clonePlugin->I_PluginAliasName = this->I_PluginAliasName;
    _clonePlugin->I_PluginVersion = this->I_PluginVersion;
    _clonePlugin->I_PluginAuther = this->I_PluginAuther;
    _clonePlugin->I_PluginComment = this->I_PluginComment;
    _clonePlugin->I_PluginFilePath = this->I_PluginFilePath;
    _clonePlugin->I_PluginTag = this->I_PluginTag;
    _clonePlugin->I_PluginAuthority = this->I_PluginAuthority;

    _clonePlugin->I_IsCopy = true;

    _clonePlugin->I_CopyID = copyID;
    _clonePlugin->I_CopyAliasName = copyAliasName;
    _clonePlugin->I_CopyComment = copyComment;

    _clonePlugin->I_PluginVar = this->I_PluginVar;
    _clonePlugin->I_PluginVarList = this->I_PluginVarList;
    _clonePlugin->I_FunctionList = this->I_FunctionList;
    _clonePlugin->I_WidgetList = this->I_WidgetList;
    return _clonePlugin;
}

bool PluginIO::ConnectCore(QObject* core){

    _core = (QCPF_Interface*)(core);

    return _core?true:false;
}

bool PluginIO::ConnectViewModel(QObject *view){

    _view = (QCPF_ViewModel*)view;

    InitFunctionList();
    InitWidgetList();

    return _view?true:false;
}

void PluginIO::slot_Action(bool checkState){
    QAction *action = (QAction*)sender();
    QString actionName =  action->property("ItemActionName").toString();

    foreach (PluginFunctionInfo* pfi, I_FunctionList) {
        if(pfi->_functonName == action->text() || pfi->_functonName == actionName)
        {
            pfi->pFunction(checkState);
            break;
        }
    }
}

void ShowViewEditor(bool);
void PluginIO::InitFunctionList()
{
    PluginFunctionInfo* pai = new PluginFunctionInfo();
    pai->_functonName = tr("View editor");
    pai->_functionDetail = tr("It's used for editing menubar,toolbar,statusbar,workspace and any other ui elements of main appliction frame.");
    pai->pFunction = &ShowViewEditor;

    I_FunctionList.append(pai);
}

void PluginIO::InitWidgetList()
{
    PluginWidgetInfo *nFormInfo = new PluginWidgetInfo();

    nFormInfo->_showType = ST_POPUP;
    nFormInfo->_widget = new ViewEditor(_view);
    nFormInfo->_widget->setObjectName(QStringLiteral("wdt_ViewEditor"));
    nFormInfo->_origWidth = nFormInfo->_widget->width();
    nFormInfo->_origWidth = nFormInfo->_widget->height();
    nFormInfo->_widgetDetail = tr("It's used for editing the view that refer to menu,toolbar,worke eara and status bar.");

    PluginIO::I_WidgetList.append(nFormInfo);
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

int PluginIO::OnViewModelInitialize(){

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
void ShowViewEditor(bool checkState)
{
    if(instance->I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == QStringLiteral("wdt_ViewEditor"))
            {
                ((QDialog*)pwi->_widget)->exec();
            }
        }
    }
}

