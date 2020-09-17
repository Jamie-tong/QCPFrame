#include "PluginIO.h"

#include <QVariant>
#include <QStringLiteral>
#include <QAction>

class MyClass
{
public:
    int Var1;
    QString Var2;
    double Var3;
};
Q_DECLARE_METATYPE(MyClass)

PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;
    PluginIO::I_PluginID = QStringLiteral("QPlugin4");
    PluginIO::I_PluginType = PT_NON_SYS;
    PluginIO::I_PluginAliasName = QStringLiteral("QPlugin4");
    PluginIO::I_PluginAuther = QStringLiteral("Jamie.T");
    PluginIO::I_PluginVersion = QStringLiteral("1.0.0.4");
    PluginIO::I_PluginComment = QStringLiteral("QPlugin4 comment");
    PluginIO::I_PluginAuthority = AT_USER1;
    PluginIO::I_IsCopy = false;
    PluginIO::I_PluginTag = QStringLiteral("NON-SINGLETON\\NON_SYSTEM\\DataSave");
}

PluginIO::~PluginIO(){}

PluginIO* PluginIO::getInstance()
{
    return instance;
}

//接口方法实现
/***************************************************
*                       方法接口                    *
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

}

void PluginIO::InitFunctionList(PluginIO* plugin)
{

}

void PluginIO::InitWidgetList(PluginIO* plugin)
{

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
