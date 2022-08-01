#include "PluginIO.h"

#include <QWidget>
#include <QVariant>

#include "pluginform2.h"
#include <QStringLiteral>
#include <QAction>
#include "wdt_hud.h"
#include "wdt_parampanel.h"

PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;

    I_PluginID = "QPlugin2";
    I_PluginAliasName = "QPlugin2";
    I_PluginAuther = "Jamie.T";
    I_PluginVersion = "1.0.0.3";
    I_PluginComment = tr("QPlugin2 comment");
    I_PluginTag = "NON-SINGLETON\\NON_SYSTEM\\DataUpLoad";
    I_PluginAuthority = AT_USER1;
}

PluginIO::~PluginIO(){}

PluginIO* PluginIO::getInstance()
{
    return instance;
}

void PluginIO::InitWidgetList(Plugin_Interface* plugin)
{
    //-----------------
    PluginWidgetInfo *nWdtHud = new PluginWidgetInfo();
    nWdtHud->_widget = new wdt_Hud();
    nWdtHud->_origWidth = nWdtHud->_widget->width();
    nWdtHud->_origHeight = nWdtHud->_widget->height();
    nWdtHud->_widgetDetail = tr("hud control.");
    plugin->I_WidgetList.append(nWdtHud);
    //-----------------
    PluginWidgetInfo *nWdtParamPanel = new PluginWidgetInfo();
    nWdtParamPanel->_widget = new wdt_ParamPanel();
    nWdtParamPanel->_origWidth = nWdtParamPanel->_widget->width();
    nWdtParamPanel->_origHeight = nWdtParamPanel->_widget->height();
    nWdtParamPanel->_widgetDetail = tr("paramPanel.");
    plugin->I_WidgetList.append(nWdtParamPanel);
}
