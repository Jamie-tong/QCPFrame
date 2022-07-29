#include "PluginIO.h"

#include <QWidget>
#include <QVariant>
#include <qobject.h>

#include <QStringLiteral>
#include <QAction>

#include "sumwidgetfortoolbar.h"
#include "wdt_map.h"
#include "wdt_search.h"

PluginIO::PluginIO()
{
    I_PluginID = QStringLiteral("QPlugin1");
    I_PluginAliasName = QStringLiteral("QPlugin1");
    I_PluginAuther = QStringLiteral("Jamie.T");
    I_PluginVersion = QStringLiteral("1.0.0.2");
    I_PluginComment = QStringLiteral("QPlugin1 Comment");
    I_PluginTag = QStringLiteral("NON-SINGLETON\\NON_SYSTEM\\DataDownLoad");
    I_PluginAuthority = AT_USER1;
}

PluginIO::~PluginIO(){}

void PluginIO::InitActionList(Plugin_Interface* plugin)
{
    //--------------------------------------------
    PluginActionInfo* paiSum = new PluginActionInfo();
    paiSum->_actionName = tr("Sum");
    paiSum->_actionDetail = tr("Sum two data at backgroud.");
    paiSum->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiSum);

    //--------------------------------------------
    PluginActionInfo* paiWave = new PluginActionInfo();
    paiWave->_actionName = tr("Wave");
    paiWave->_actionDetail = tr("");
    paiWave->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiWave);

    //--------------------------------------------
    PluginActionInfo* paiDatabase = new PluginActionInfo();
    paiDatabase->_actionName = tr("Database");
    paiDatabase->_actionDetail = tr("");
    paiDatabase->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiDatabase);

    //--------------------------------------------
    PluginActionInfo* paiNet = new PluginActionInfo();
    paiNet->_actionName = tr("Net");
    paiNet->_actionDetail = tr("");
    paiNet->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiNet);

    //--------------------------------------------
    PluginActionInfo* paiPython = new PluginActionInfo();
    paiPython->_actionName = tr("Python");
    paiPython->_actionDetail = tr("");
    paiPython->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiPython);

    //--------------------------------------------
    PluginActionInfo* paiPlane = new PluginActionInfo();
    paiPlane->_actionName = tr("Plane");
    paiPlane->_actionDetail = tr("");
    paiPlane->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiPlane);

    //--------------------------------------------
    PluginActionInfo* paiReport = new PluginActionInfo();
    paiReport->_actionName = tr("Report");
    paiReport->_actionDetail = tr("");
    paiReport->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiReport);

    //--------------------------------------------
    PluginActionInfo* paiSearch = new PluginActionInfo();
    paiSearch->_actionName = tr("Search");
    paiSearch->_actionDetail = tr("");
    paiSearch->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiSearch);
}

void PluginIO::InitWidgetList(Plugin_Interface* plugin)
{
    PluginWidgetInfo *nWdtSum = new PluginWidgetInfo();

    nWdtSum->_showType = ST_DOCK;
    nWdtSum->_widget = new SumWidgetForToolbar();
    nWdtSum->_origWidth = nWdtSum->_widget->width();
    nWdtSum->_origHeight = nWdtSum->_widget->height();
    nWdtSum->_widgetDetail = tr("sum function.");
    plugin->I_WidgetList.append(nWdtSum);

    //----------------------------
    PluginWidgetInfo *nWdtSearch = new PluginWidgetInfo();

    nWdtSearch->_showType = ST_DOCK;
    nWdtSearch->_widget = new wdt_search();
    nWdtSearch->_origWidth = nWdtSearch->_widget->width();
    nWdtSearch->_origHeight = nWdtSearch->_widget->height();
    nWdtSearch->_widgetDetail = tr("search function.");
    plugin->I_WidgetList.append(nWdtSearch);

    //----------------------------
    PluginWidgetInfo *nWdtMap = new PluginWidgetInfo();

    nWdtMap->_showType = ST_DOCK;
    nWdtMap->_widget = new wdt_Map(_core);
    nWdtMap->_origWidth = nWdtMap->_widget->width();
    nWdtMap->_origHeight = nWdtMap->_widget->height();
    nWdtMap->_widgetDetail = tr("map control.");
    plugin->I_WidgetList.append(nWdtMap);
}

void PluginIO::Action_SumWidget(bool checkState)
{
    int i = 3+4;

    tInfo._type = INFT_MSG_INFO;
    tInfo._title = QStringLiteral("sum");
    tInfo._content = QStringLiteral("the end = 7");
    emit sig_OutputInfo(tInfo);
}
