#include "PluginIO.h"

#include <QVariant>
#include <QStringLiteral>
#include <QAction>


PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;

    I_PluginID = QStringLiteral("QPlugin4");
    I_PluginAliasName = QStringLiteral("QPlugin4");
    I_PluginAuther = QStringLiteral("Jamie.T");
    I_PluginVersion = QStringLiteral("1.0.0.4");
    I_PluginComment = QStringLiteral("QPlugin4 comment");
    I_PluginAuthority = AT_USER1;
    I_PluginTag = QStringLiteral("NON-SINGLETON\\NON_SYSTEM\\DataSave");
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
