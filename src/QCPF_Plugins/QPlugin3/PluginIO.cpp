#include "PluginIO.h"

#include <QVariant>
#include <QStringLiteral>
#include <QAction>
#include <QThread>

#include "StepUp.h"
#include "stepdown.h"
#include <QTimer>

PluginIO* instance;

PluginIO::PluginIO()
{
    PluginIO::I_PluginID = QStringLiteral("QPlugin3");
    PluginIO::I_PluginType = PT_NON_SYS;
    PluginIO::I_PluginAliasName = QStringLiteral("QPlugin3");
    PluginIO::I_PluginAuther = QStringLiteral("Jamie.T");
    PluginIO::I_PluginVersion = QStringLiteral("1.0.0.3");
    PluginIO::I_PluginComment = QStringLiteral("QPlugin3 comment");
    PluginIO::I_PluginTag = QStringLiteral("NON-SINGLETON\\NON_SYSTEM\\DataHandle");
    PluginIO::I_PluginAuthority = AT_USER1;

    PluginIO::I_IsCopy = false;
}

PluginIO::~PluginIO(){}

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
    //--------------------------------------------
    PluginActionInfo* pai1 = new PluginActionInfo();
    pai1->_actionName = tr("StepUp");
    pai1->_actionDetail = tr("Step Up form 0 ~ 10.");
    pai1->_pAction = (FPTR_ACTION)(&PluginIO::Action_sum);

    plugin->I_ActionList.append(pai1);
}

void PluginIO::InitFunctionList(PluginIO* plugin)
{
    //--------------------------------------------
    PluginFunctionInfo* pai_stepUp = new PluginFunctionInfo();
    pai_stepUp->_functionName = tr("StepUp");
    pai_stepUp->_functionDetail = tr("Step Up form 0 ~ 10.");
    pai_stepUp->_pFunction = (FPTR_FUNC_CLS)(&PluginIO::Function_StepUp);

    plugin->I_FunctionList.append(pai_stepUp);

    //--------------------------------------------
    PluginFunctionInfo* pai_stepDown = new PluginFunctionInfo();
    pai_stepDown->_functionName = tr("StepDown");
    pai_stepDown->_functionDetail = tr("Step Up form 10 ~ 0.");
    pai_stepDown->_pFunction = (FPTR_FUNC_CLS)(&PluginIO::Function_StepDown);

    plugin->I_FunctionList.append(pai_stepDown);

    //--------------------------------------------
    PluginFunctionInfo* pai_stepStartTimer = new PluginFunctionInfo();
    pai_stepStartTimer->_functionName = tr("StepTimer");
    pai_stepStartTimer->_functionDetail = tr("Start Timer Step Up");
    pai_stepStartTimer->_pFunction = (FPTR_FUNC_CLS)(&PluginIO::Function_StepStartTimer);

    plugin->I_FunctionList.append(pai_stepStartTimer);

    //--------------------------------------------
    PluginFunctionInfo* pai_stepThread = new PluginFunctionInfo();
    pai_stepThread->_functionName = tr("StepThread");
    pai_stepThread->_functionDetail = tr("Thread1 Step Up form 0 ~ 10. and Thread2 Step Down form 100 ~ 90");
    pai_stepThread->_pFunction = (FPTR_FUNC_CLS)(&PluginIO::Function_StepThread);

    plugin->I_FunctionList.append(pai_stepThread);

    tagOutputInfo tInfo;
    tInfo._type = INFT_STATUS_INFO;
    tInfo._title = QStringLiteral("Sum");
    tInfo._content = QString("the Sum Action end = %1");
    emit sig_OutputInfo(tInfo);
}

void PluginIO::InitWidgetList(PluginIO* plugin)
{

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
void PluginIO::Action_sum(bool checkState)
{
    int sum = 1+1;

    tagOutputInfo tInfo;
    tInfo._type = INFT_STATUS_INFO;
    tInfo._title = QStringLiteral("Sum");
    tInfo._content = QString("the Sum Action end = %1").arg(sum);
    emit sig_OutputInfo(tInfo);
}

int PluginIO::Function_StepUp(QVariant arg_in, QVariant& arg_out)
{
    int i = 0;
    tagOutputInfo tInfo;
    while(i<10)
    {
        i++;
        tInfo._type = INFT_STATUS_INFO;
        tInfo._title = QStringLiteral("StepUp");
        tInfo._content = QString("the StepUp end = %1").arg(i);
        emit sig_OutputInfo(tInfo);

        QThread::msleep(200);
    }

    return 0;
}

int PluginIO::Function_StepDown(QVariant arg_in, QVariant& arg_out)
{
    int i = 10;

    tagOutputInfo tInfo;
    while(i>0)
    {
        tInfo._type = INFT_STATUS_INFO;
        tInfo._title = QStringLiteral("StepDown");
        tInfo._content = QString("the StepDown end = %1").arg(i);
        emit sig_OutputInfo(tInfo);
         i--;
        QThread::msleep(200);
    }

    return 1;
}

int PluginIO::Function_StepStartTimer(QVariant arg_in, QVariant &arg_out)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    timer->start(500);

    return 0;
}

void PluginIO::handleTimeout()
{
    tagOutputInfo tInfo;
    tInfo._type = INFT_STATUS_INFO;
    tInfo._title = QStringLiteral("Timeout");
    tInfo._content = QString("the Timer Started.");
    emit sig_OutputInfo(tInfo);
}

int PluginIO::Function_StepThread(QVariant arg_in, QVariant& arg_out)
{
    StepUp* _up = new StepUp();
    StepDown* _down = new StepDown();

    _up->start();
    _down->start();

    arg_out = true;
    return 2;
}
