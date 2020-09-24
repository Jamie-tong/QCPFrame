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

#include <QStringLiteral>
#include <QAction>

#include "usermanager.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

PluginIO* instance;
PluginIO::PluginIO()
{
    instance = this;

    I_PluginID = tr("QCPF_UserManager");
    I_PluginAliasName = tr("User Manager");
    I_PluginAuther = tr("Jamie.T");
    I_PluginVersion = tr("1.0.0.1");
    I_PluginComment = tr("Manage users.");
    I_PluginTag = tr("SINGLETON\\SYSTEM\\USER_MANAGER");
    I_PluginAuthority = AT_MANAGER1;

    //GetUsersInfoFromJson();不能放在这里，基类的_core还没构造完
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
int PluginIO::OnCoreInitialize()
{
    return GetUsersInfoFromJson();
}

void PluginIO::InitActionList(Plugin_Interface* plugin)
{
    PluginActionInfo* pai = new PluginActionInfo();
    pai->_actionName = tr("User Manager");
    pai->_actionDetail = tr("User Manager.");
    pai->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowUserManager);

    plugin->I_ActionList.append(pai);

}

void PluginIO::InitFunctionList(Plugin_Interface* plugin)
{
    //--------------------------------------------
    PluginFunctionInfo* pfi_verifyLoginInfo = new PluginFunctionInfo();
    pfi_verifyLoginInfo->_functionName = tr("VerifyLoginInfo");
    pfi_verifyLoginInfo->_functionDetail = tr("Verify login info.");
    pfi_verifyLoginInfo->_pFunction = (FPTR_FUNC_CLS)(&PluginIO::Function_VerifyLoginInfo);

    plugin->I_FunctionList.append(pfi_verifyLoginInfo);
}

void PluginIO::InitWidgetList(Plugin_Interface* plugin)
{
    QCPF_Model* core = (QCPF_Model*)_core;
    PluginWidgetInfo *nFormInfo = new PluginWidgetInfo();

    nFormInfo->_showType = ST_POPUP;
    nFormInfo->_widget = new UserManager(core);
    nFormInfo->_origWidth = nFormInfo->_widget->width();
    nFormInfo->_origHeight = nFormInfo->_widget->height();
    nFormInfo->_widgetDetail = tr("It's used for managing the Non-System plugins");

    plugin->I_WidgetList.append(nFormInfo);
}

int PluginIO::GetUsersInfoFromJson()
{
    QFile file(_core->I_ApplicationDirPath + "/Data/User/Users.json");
    if(!file.open(QIODevice::ReadOnly))
        return -1;

    QByteArray allData = file.readAll();
    file.close();

    //进行JSON相关的处理
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
        return -2;

    QJsonObject rootObj = jsonDoc.object();
    //数据存入QJsonObject格式的rootObj中
    if (rootObj.contains("Users"))
    {
        QJsonValue value = rootObj.value("Users");
        if (value.isArray())
        {
            QJsonArray array = value.toArray();
            int nSize = array.size();
            for (int i = 0; i < nSize; ++i)
            {
                UserInfo* tUser = new UserInfo();
                tUser->_userName = array.at(i).toObject().value("UserName").toString();
                tUser->_password = array.at(i).toObject().value("Password").toString();
                tUser->_authority = (AuthorityType)array.at(i).toObject().value("Authority").toInt();
                tUser->_createDatetime = array.at(i).toObject().value("Datetime").toString();
                _core->I_UserInfoLst.append(tUser);
            }
        }
    }

    return 0;
}

/***********************************************************************
 *  action 函数指针所对应的回调函数
 * *********************************************************************/
void PluginIO::Action_ShowUserManager(bool checkState)
{
    QAction* actSender = (QAction*)sender();
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == QStringLiteral("UserManager"))
            {
                pwi->_widget->setWindowIcon(actSender->icon());
                ((QDialog*)pwi->_widget)->exec();
            }
        }
    }
}

struct tagUserInfo{
    QString userName;
    QString password;
};
Q_DECLARE_METATYPE(tagUserInfo)

int PluginIO::Function_VerifyLoginInfo(QVariant arg_in, QVariant& arg_out)
{
    arg_out = false;

    if(arg_in.canConvert<tagUserInfo>())
    {
        tagUserInfo userInfo =arg_in.value<tagUserInfo>();
        foreach (UserInfo* uInfo, _core->I_UserInfoLst) {
            if(uInfo->_userName == userInfo.userName && uInfo->_password == userInfo.password)
            {
                _core->I_CurrentUserInfo._userName = uInfo->_userName;
                _core->I_CurrentUserInfo._password = uInfo->_password;
                _core->I_CurrentUserInfo._authority = uInfo->_authority;
                _core->I_CurrentUserInfo._createDatetime = uInfo->_createDatetime;
                _core->I_CurrentUserInfo._detail = uInfo->_detail;
                arg_out = true;
                break;
            }
        }
    }

    return 0;
}
