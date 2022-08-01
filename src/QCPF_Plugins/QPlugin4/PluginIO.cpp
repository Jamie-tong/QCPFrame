#include "PluginIO.h"

#include <QVariant>
#include <QStringLiteral>
#include <QAction>


PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;

    I_PluginID = "QPlugin4";
    I_PluginAliasName = "QPlugin4";
    I_PluginAuther = "Jamie.T";
    I_PluginVersion = "1.0.0.5";
    I_PluginComment = tr("QPlugin4 comment");
    I_PluginAuthority = AT_USER1;
    I_PluginTag = "NON-SINGLETON\\NON_SYSTEM\\DataSave";
}

PluginIO::~PluginIO(){}

PluginIO* PluginIO::getInstance()
{
    return instance;
}

