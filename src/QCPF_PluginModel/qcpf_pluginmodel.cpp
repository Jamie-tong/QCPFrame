#include "qcpf_pluginmodel.h"

#include <QWidget>
#include <QVariant>
#include <qobject.h>

#include <QStringLiteral>
#include <QAction>

QCPF_PluginModel::QCPF_PluginModel()
{
    I_IsCopy = false;
}

QCPF_PluginModel::~QCPF_PluginModel()
{
}

//接口方法实现
/***************************************************
*                       方法接口                                       *
***************************************************/
bool QCPF_PluginModel::ConnectCore(QObject* core){

    _core = (QCPF_Model*)(core);
    InitActionList(this);
    InitFunctionList(this);
    if(_core->I_RunMode == RM_APPLICATION)
            InitWidgetList(this);

    return _core?true:false;
}

void QCPF_PluginModel::slot_Action(bool checkState){
    QAction *action = (QAction*)sender();
    QString actionName =  action->property("ItemActionName").toString();

    foreach (PluginActionInfo* pai, I_ActionList) {
        if(pai->_actionName == action->text() || pai->_actionName == actionName)
        {
            pai->_actionIcon = action->icon();
            (this->*pai->_pAction)(checkState);
            break;
        }
    }
}

