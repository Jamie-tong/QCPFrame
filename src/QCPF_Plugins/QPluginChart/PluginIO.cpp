#include "PluginIO.h"

#include <QWidget>
#include <QVariant>

#include <QStringLiteral>
#include <QAction>
#include "wdt_zoomchart.h"
#include "wdt_areachart.h"
#include "wdt_audio.h"

PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;

    I_PluginID = QStringLiteral("QPluginChart");
    I_PluginAliasName = QStringLiteral("QPluginChart");
    I_PluginAuther = QStringLiteral("Jamie.T");
    I_PluginVersion = QStringLiteral("1.0.0.1");
    I_PluginComment = QStringLiteral("Custom chart");
    I_PluginTag = QStringLiteral("");
    I_PluginAuthority = AT_USER1;
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
void PluginIO::InitWidgetList(Plugin_Interface* plugin)
{
    //-----------------
    PluginWidgetInfo *nWdtZoomChart = new PluginWidgetInfo();
    nWdtZoomChart->_widget = new wdt_ZoomChart();
    nWdtZoomChart->_origWidth = nWdtZoomChart->_widget->width();
    nWdtZoomChart->_origHeight = nWdtZoomChart->_widget->height();
    nWdtZoomChart->_widgetDetail = tr("zoom chart.");
    plugin->I_WidgetList.append(nWdtZoomChart);

    //-----------------
    PluginWidgetInfo *nWdtAreaChart = new PluginWidgetInfo();
    nWdtAreaChart->_widget = new wdt_AreaChart();
    nWdtAreaChart->_origWidth = nWdtAreaChart->_widget->width();
    nWdtAreaChart->_origHeight = nWdtAreaChart->_widget->height();
    nWdtAreaChart->_widgetDetail = tr("area chart.");
    plugin->I_WidgetList.append(nWdtAreaChart);

    //-----------------
    PluginWidgetInfo *nWdtAudioChart = new PluginWidgetInfo();
    nWdtAudioChart->_widget = new wdt_Audio();
    nWdtAudioChart->_origWidth = nWdtAudioChart->_widget->width();
    nWdtAudioChart->_origHeight = nWdtAudioChart->_widget->height();
    nWdtAudioChart->_widgetDetail = tr("audio chart.");
    plugin->I_WidgetList.append(nWdtAudioChart);

}
