#include "PluginIO.h"

#include <QWidget>
#include <QVariant>
#include <qobject.h>

#include <QStringLiteral>
#include <QAction>

#include "sumwidgetfortoolbar.h"
#include "wdt_map.h"

PluginIO::PluginIO()
{
    I_PluginID = QStringLiteral("QPlugin1");
    I_PluginAliasName = QStringLiteral("QPlugin1");
    I_PluginAuther = QStringLiteral("Jamie.T");
    I_PluginVersion = QStringLiteral("1.0.0.1");
    I_PluginComment = QStringLiteral("QPlugin1 Comment");
    I_PluginTag = QStringLiteral("NON-SINGLETON\\NON_SYSTEM\\DataDownLoad");
    I_PluginAuthority = AT_USER1;
}

PluginIO::~PluginIO(){}

//接口方法实现
/***************************************************
*                       方法接口                                       *
***************************************************/
void PluginIO::InitActionList(Plugin_Interface* plugin)
{
    //--------------------------------------------
    PluginActionInfo* pai1 = new PluginActionInfo();
    pai1->_actionName = tr("Sum");
    pai1->_actionDetail = tr("Sum two data at backgroud.");
    pai1->_pAction = (FPTR_ACTION)(&PluginIO::Action_SumWidget);

    plugin->I_ActionList.append(pai1);
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
    PluginWidgetInfo *nWdtMap = new PluginWidgetInfo();

    nWdtMap->_showType = ST_DOCK;
    nWdtMap->_widget = new wdt_Map(_core);
    nWdtMap->_origWidth = nWdtMap->_widget->width();
    nWdtMap->_origHeight = nWdtMap->_widget->height();
    nWdtMap->_widgetDetail = tr("map control.");
    plugin->I_WidgetList.append(nWdtMap);
}

/***********************************************************************
 *  action 函数指针所对应的回调函数
 * *********************************************************************/
void PluginIO::Action_SumWidget(bool checkState)
{
    int i = 3+4;

    tInfo._type = INFT_MSG_INFO;
    tInfo._title = QStringLiteral("sum");
    tInfo._content = QStringLiteral("the end = 7");
    emit sig_OutputInfo(tInfo);
}
