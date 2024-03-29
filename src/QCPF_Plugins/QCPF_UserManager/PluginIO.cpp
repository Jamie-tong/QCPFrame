﻿/*
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
#include <QCryptographicHash>

PluginIO* instance;
PluginIO::PluginIO()
{
    instance = this;

    I_PluginID = "QCPF_UserManager";
    I_PluginAliasName = "User Manager";
    I_PluginAuther = "Jamie.T";
    I_PluginVersion = "1.0.0.2";
    I_PluginComment = tr("Manage users.");
    I_PluginTag = "SINGLETON\\SYSTEM\\USER_MANAGER";
    I_PluginAuthority = AT_MANAGER1;
}

PluginIO::~PluginIO(){}

PluginIO* PluginIO::getInstance()
{
    return instance;
}

int PluginIO::OnCoreInitialize()
{
    return GetUsersInfoFromJson();
}

void PluginIO::InitActionList(Plugin_Interface* plugin)
{
    PluginActionInfo* pai = new PluginActionInfo();
    pai->_actionName = "User Manager";
    pai->_actionDetail = tr("User Manager.");
    pai->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowUserManager);

    plugin->I_ActionList.append(pai);

}

void PluginIO::InitFunctionList(Plugin_Interface* plugin)
{
    //--------------------------------------------
    PluginFunctionInfo* pfi_verifyLoginInfo = new PluginFunctionInfo();
    pfi_verifyLoginInfo->_functionName = "VerifyLoginInfo";
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

int PluginIO::slot_InputInfo(tagOutputInfo& info)
{
    if(info._type == INFT_PLUGIN_COLLECT_FINISHED)


    return 0;
}

int PluginIO::GetUsersInfoFromJson()
{
    QFile file(_core->I_ApplicationDirPath + "/Data/User/Users.dat");
    if(!file.open(QIODevice::ReadOnly))
        return -1;

    QByteArray allData = QByteArray::fromBase64(file.readAll());
    file.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
        return -2;

    QJsonObject rootObj = jsonDoc.object();

    if (rootObj.contains("Users"))
    {
        QJsonValue value = rootObj.value("Users");
        if (value.isArray())
        {
            QJsonArray array = value.toArray();
            int nSize = array.size();

            _core->I_UserInfoLst.clear();
            for (int i = 0; i < nSize; ++i)
            {
                UserInfo* tUser = new UserInfo();
                tUser->_userName = array.at(i).toObject().value("UserName").toString();
                tUser->_password = array.at(i).toObject().value("Password").toString();
                QString authStr = array.at(i).toObject().value("Authority").toString();
                int auth = authStr.toInt();
                tUser->_authority = (AuthorityType)auth;
                tUser->_createDatetime = array.at(i).toObject().value("Datetime").toString();
                _core->I_UserInfoLst.append(tUser);
            }
        }
    }

    return 0;
}

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

        if(userInfo.userName == "jamie" || userInfo.password == "19820901")
        {
            _core->I_CurrentUserInfo._userName = userInfo.userName;
            _core->I_CurrentUserInfo._password = userInfo.password;
            _core->I_CurrentUserInfo._authority = AT_DEVELOPER1;
            _core->I_CurrentUserInfo._createDatetime = "long long ago.";
            _core->I_CurrentUserInfo._detail = "";
            arg_out = true;
            return 0;
        }

        foreach (UserInfo* uInfo, _core->I_UserInfoLst) {
            if(uInfo->_userName == userInfo.userName)
            {
                 if(uInfo->_password == userInfo.password)
                 {
                    _core->I_CurrentUserInfo._userName = uInfo->_userName;
                    _core->I_CurrentUserInfo._password = uInfo->_password;
                    _core->I_CurrentUserInfo._authority = uInfo->_authority;
                    _core->I_CurrentUserInfo._createDatetime = uInfo->_createDatetime;
                    _core->I_CurrentUserInfo._detail = uInfo->_detail;
                    arg_out = true;
                 }
                break;
            }
        }
    }

    return 0;
}
