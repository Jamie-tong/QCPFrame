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
#include <QMessageBox>

PluginIO* instance;

PluginIO::PluginIO()
{
    instance = this;

    I_PluginID = "QCPF_ViewEditor";
    I_PluginAliasName = "View Editor";
    I_PluginAuther = "Jamie.T";
    I_PluginVersion = "1.1.0.1";
    I_PluginComment = tr("Edit the view of main window, such as menu-bar, tool-bar, status-bar and workspace.");
    I_PluginTag = "SINGLETON\\SYSTEM\\VIEW_EDITER";
    I_PluginAuthority = AT_DEVELOPER1;
}

PluginIO::~PluginIO(){}

PluginIO* PluginIO::getInstance()
{
    return instance;
}

void PluginIO::InitActionList(Plugin_Interface* plugin)
{
    //--------------------------------------------
    PluginActionInfo* pai1 = new PluginActionInfo();
    pai1->_actionName = "View editor";
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

int PluginIO::slot_InputInfo(tagOutputInfo& info)
{
    if(info._type == INFT_PLUGIN_COLLECT_FINISHED)
        ViewEditor::getInstance()->setConfigToUI();
    else if(info._type == INFT_VIEW_CONFIG_CHANGED)
    {
        if(ViewEditor::getInstance()!=nullptr)
        {
            QMessageBox::information(ViewEditor::getInstance(), tr("information"), tr("View configuration has changed, please restart application for updating."));
            ViewEditor::getInstance()->close();
        }
    }

    return 0;
}

void PluginIO::Action_ShowViewEditor(bool checkState)
{
    QAction* actSender = (QAction*)sender();
    if(I_WidgetList.count()>0)
    {
        foreach (PluginWidgetInfo* pwi, instance->I_WidgetList) {
            if(pwi->_widget->objectName() == QStringLiteral("wdt_ViewEditor"))
            {
                pwi->_widget->setWindowIcon(actSender->icon());
                ((QDialog*)pwi->_widget)->show();
            }
        }
    }
}

