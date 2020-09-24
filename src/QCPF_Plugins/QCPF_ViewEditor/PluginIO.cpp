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

#include "ViewEditor.h"
#include <QStringLiteral>
#include <QAction>

PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;

    I_PluginID = tr("QCPF_ViewEditor");
    I_PluginAliasName = tr("View Editor");
    I_PluginAuther = tr("Jamie.T");
    I_PluginVersion = tr("1.0.0.2");
    I_PluginComment = tr("Edit the view of main window, such as menu-bar, tool-bar, status-bar and workspace.");
    I_PluginTag = tr("SINGLETON\\SYSTEM\\VIEW_EDITER");
    I_PluginAuthority = AT_DEVELOPER1;
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
void PluginIO::InitActionList(Plugin_Interface* plugin)
{
    //--------------------------------------------
    PluginActionInfo* pai1 = new PluginActionInfo();
    pai1->_actionName = tr("View editor");
    pai1->_actionDetail = tr("It's used for editing menubar,toolbar,statusbar,workspace and any other ui elements of main appliction frame.");
    pai1->_pAction = (FPTR_ACTION)(&PluginIO::Action_ShowViewEditor);

    plugin->I_ActionList.append(pai1);
}

void PluginIO::InitWidgetList(Plugin_Interface* plugin)
{
    PluginWidgetInfo *nWdtViewEditor = new PluginWidgetInfo();

    nWdtViewEditor->_showType = ST_POPUP;
    nWdtViewEditor->_widget = new ViewEditor();
    nWdtViewEditor->_widget->setObjectName(QStringLiteral("wdt_ViewEditor"));
    nWdtViewEditor->_origWidth = nWdtViewEditor->_widget->width();
    nWdtViewEditor->_origWidth = nWdtViewEditor->_widget->height();
    nWdtViewEditor->_widgetDetail = tr("It's used for editing the view that refer to menu,toolbar,worke eara and status bar.");

    plugin->I_WidgetList.append(nWdtViewEditor);
}

/***********************************************************************
 *  action 函数指针所对应的回调函数
 * *********************************************************************/
void PluginIO::Action_ShowViewEditor(bool checkState)
{
    QAction* actSender = (QAction*)sender();
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == QStringLiteral("wdt_ViewEditor"))
            {
                pwi->_widget->setWindowIcon(actSender->icon());
                ((QDialog*)pwi->_widget)->exec();
            }
        }
    }
}

