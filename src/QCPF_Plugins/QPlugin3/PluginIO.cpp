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
    I_PluginID = QStringLiteral("QPlugin3");
    I_PluginAliasName = QStringLiteral("QPlugin3");
    I_PluginAuther = QStringLiteral("Jamie.T");
    I_PluginVersion = QStringLiteral("1.0.0.4");
    I_PluginComment = QStringLiteral("QPlugin3 comment");
    I_PluginTag = QStringLiteral("NON-SINGLETON\\NON_SYSTEM\\DataHandle");
    I_PluginAuthority = AT_USER1;
}

PluginIO::~PluginIO(){}

void PluginIO::InitActionList(Plugin_Interface* plugin)
{
    //--------------------------------------------
    PluginActionInfo* pai1 = new PluginActionInfo();
    pai1->_actionName = tr("StepUp");
    pai1->_actionDetail = tr("Step Up form 0 ~ 10.");
    pai1->_pAction = (FPTR_ACTION)(&PluginIO::Action_sum);

    plugin->I_ActionList.append(pai1);
}

void PluginIO::InitFunctionList(Plugin_Interface* plugin)
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
