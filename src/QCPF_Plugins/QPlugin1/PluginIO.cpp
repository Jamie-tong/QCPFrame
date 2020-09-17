#include "PluginIO.h"

#include <QWidget>
#include <QVariant>
#include <qobject.h>

#include <QStringLiteral>
#include <QAction>

#include "sumwidgetfortoolbar.h"
#include "wdt_map.h"

PluginIO::PluginIO()
{
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

    foreach(QVariant v, this->I_PluginVarList)
        _clonePlugin->I_PluginVarList.append(v);

    //action没必要深拷贝，保持和原始组件一样的触发功能即可
    _clonePlugin->I_ActionList = this->I_ActionList;
    //function和widget需要深拷贝
    InitFunctionList(_clonePlugin);
    if(_core->I_RunMode == RM_APPLICATION)
            InitWidgetList(_clonePlugin);

    return _clonePlugin;
}

bool PluginIO::ConnectCore(QObject* core){

    _core = (QCPF_Interface*)(core);
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
    pai1->_actionName = tr("Sum");
    pai1->_actionDetail = tr("Sum two data at backgroud.");
    pai1->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(pai1);
}

void PluginIO::InitFunctionList(PluginIO* plugin)
{

}

void PluginIO::InitWidgetList(PluginIO* plugin)
{
    PluginWidgetInfo *nWdtSum = new PluginWidgetInfo();

    nWdtSum->_showType = ST_DOCK;
    nWdtSum->_widget = new SumWidgetForToolbar();
    nWdtSum->_origWidth = nWdtSum->_widget->width();
    nWdtSum->_origHeight = nWdtSum->_widget->height();
    nWdtSum->_widgetDetail = tr("sum function.");
    plugin->PluginIO::I_WidgetList.append(nWdtSum);

    //----------------------------
    PluginWidgetInfo *nWdtMap = new PluginWidgetInfo();

    nWdtMap->_showType = ST_DOCK;
    nWdtMap->_widget = new wdt_Map(_core);
    nWdtMap->_origWidth = nWdtMap->_widget->width();
    nWdtMap->_origHeight = nWdtMap->_widget->height();
    nWdtMap->_widgetDetail = tr("map control.");
    plugin->PluginIO::I_WidgetList.append(nWdtMap);
}

//通用方法
int PluginIO::PluginFunction(QVariant arg_in, QVariant &arg_out){

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
void PluginIO::Action_SumWidget(bool checkState)
{
    int i = 3+4;

    tInfo._type = INFT_MSG_INFO;
    tInfo._title = QStringLiteral("sum");
    tInfo._content = QStringLiteral("the end = 7");
    emit sig_OutputInfo(tInfo);
}
