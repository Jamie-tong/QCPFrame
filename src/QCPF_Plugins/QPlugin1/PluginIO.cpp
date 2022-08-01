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
    I_PluginID = "QPlugin1";
    I_PluginAliasName = "QPlugin1";
    I_PluginAuther = "Jamie.T";
    I_PluginVersion = "1.0.0.2";
    I_PluginComment = tr("QPlugin1 Comment");
    I_PluginTag = "NON-SINGLETON\\NON_SYSTEM\\DataDownLoad";
    I_PluginAuthority = AT_USER1;
}

PluginIO::~PluginIO(){}

void PluginIO::InitActionList(Plugin_Interface* plugin)
{
    //--------------------------------------------
    PluginActionInfo* paiSum = new PluginActionInfo();
    paiSum->_actionName = "Sum";
    paiSum->_actionDetail = tr("Sum two data at backgroud.");
    paiSum->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiSum);

    //--------------------------------------------
    PluginActionInfo* paiWave = new PluginActionInfo();
    paiWave->_actionName = "Wave";
    paiWave->_actionDetail = "";
    paiWave->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiWave);

    //--------------------------------------------
    PluginActionInfo* paiDatabase = new PluginActionInfo();
    paiDatabase->_actionName = "Database";
    paiDatabase->_actionDetail = "";
    paiDatabase->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiDatabase);

    //--------------------------------------------
    PluginActionInfo* paiNet = new PluginActionInfo();
    paiNet->_actionName = "Net";
    paiNet->_actionDetail = "";
    paiNet->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiNet);

    //--------------------------------------------
    PluginActionInfo* paiPython = new PluginActionInfo();
    paiPython->_actionName = "Python";
    paiPython->_actionDetail = "";
    paiPython->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiPython);

    //--------------------------------------------
    PluginActionInfo* paiPlane = new PluginActionInfo();
    paiPlane->_actionName = "Plane";
    paiPlane->_actionDetail = "";
    paiPlane->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiPlane);

    //--------------------------------------------
    PluginActionInfo* paiReport = new PluginActionInfo();
    paiReport->_actionName = "Report";
    paiReport->_actionDetail = "";
    paiReport->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(paiReport);

    //--------------------------------------------
    PluginActionInfo* paiSearch = new PluginActionInfo();
    paiSearch->_actionName = "Search";
    paiSearch->_actionDetail = "";
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
