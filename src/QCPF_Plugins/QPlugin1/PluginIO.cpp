#include "PluginIO.h"

#include <QWidget>
#include <QVariant>
#include <qobject.h>

#include <QStringLiteral>
#include <QAction>

#include "sumwidgetfortoolbar.h"
#include "wdt_map.h"

PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;
    PluginIO::I_PluginID = QStringLiteral("QPlugin1");
    PluginIO::I_PluginType = PT_NON_SYS;
    PluginIO::I_PluginAliasName = QStringLiteral("QPlugin1");
    PluginIO::I_PluginAuther = QStringLiteral("Jamie.T");
    PluginIO::I_PluginVersion = QStringLiteral("1.0.0.1");
    PluginIO::I_PluginComment = QStringLiteral("QPlugin1 Comment");
    PluginIO::I_PluginTag = QStringLiteral("NON-SINGLETON\\NON_SYSTEM\\DataDownLoad");
    PluginIO::I_PluginAuthority = AT_USER1;

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

void SumWidget(bool checkState);
void PluginIO::InitFunctionList()
{
    //--------------------------------------------
    PluginFunctionInfo* pai1 = new PluginFunctionInfo();
    pai1->_functonName = tr("Sum");
    pai1->_functionDetail = tr("Sum two data at backgroud.");
    pai1->pFunction = &SumWidget;

    I_FunctionList.append(pai1);
}

void PluginIO::InitWidgetList()
{
    PluginWidgetInfo *nFormInfo = new PluginWidgetInfo();

    nFormInfo->_showType = ST_DOCK;
    nFormInfo->_widget = new SumWidgetForToolbar();
    nFormInfo->_origWidth = nFormInfo->_widget->width();
    nFormInfo->_origHeight = nFormInfo->_widget->height();
    nFormInfo->_widgetDetail = tr("sum function.");
    PluginIO::I_WidgetList.append(nFormInfo);

    //----------------------------
    PluginWidgetInfo *nFormMap = new PluginWidgetInfo();

    nFormMap->_showType = ST_DOCK;
    nFormMap->_widget = new wdt_Map();
    nFormMap->_origWidth = nFormMap->_widget->width();
    nFormMap->_origHeight = nFormMap->_widget->height();
    nFormMap->_widgetDetail = tr("map control.");
    PluginIO::I_WidgetList.append(nFormMap);
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
void SumWidget(bool checkState)
{
    int i = 3+4;

    instance->tinfo._type = INFT_MSG_INFO;
    instance->tinfo._title = QStringLiteral("sum");
    instance->tinfo._content = QStringLiteral("the end = 7");
    emit instance->sig_OutputInfo(instance->tinfo);
}
