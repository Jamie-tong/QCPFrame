/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef QCFVIEWCONFIGMODEL_H
#define QCFVIEWCONFIGMODEL_H

#include <QObject>
#include <QString>
#include "../../interface/coreinterface.h"
#include "../../interface/plugininterface.h"

enum BarItemType
{
  BT_ACTION,
  BT_WIDGET,
  BT_SEPARATOR,
  BT_SPACER,
};

enum BarItemSytle
{
  BS_NO_TEXT,
  BS_TEXT_BESIDE_ICON,
  BS_TEXT_UNDER_ICON
};

enum StatusbarItemType
{
    SBT_COMMON,
    SBT_PERMANENT,
};

class ActionItem
{
public:
    QString _actionObjectName;
    QString _actionDetail;
    int _authority;
    bool _isEnable;
    bool _isVisible;
};

class WidgetItem
{
public:
    int _pluginType;
    QString _pluginID;
    QString _copyID;
    QString _widgetObjectName;
    QString _widgetDetail;
    int _authority;
    bool _isEnable;
    bool _isVisible;

    int _widgetOrigWidth;
    int _widgetOrigHeight;
};

class StatusbarItem : public WidgetItem
{
public:
    int _statusbarItemType;//StatusbarItemType
};

class BarItem
{
public:
    int _type;//BarItemType
    ActionItem* _actionItem;
    WidgetItem* _widgetItem;
    int _width;
    int _height;
};

class JMenuNode
{
public:
    QString _menuTitle;
    QString _menuShortCut;
    QString _menuIconPath;
    int _menuAuthority;//AuthorityType
    bool _menuIsEnable;
    bool _menuIsVisible;
    bool _menuCheckable;
    bool _menuIsSeprator;

    int _pluginType;//PluginType
    QString _pluginID;
    QString _copyID;

    QString _actionName;
    QString _actionDetail;

    QString _parentMenuTitle;
    int _count_children;
    QList<JMenuNode*> _children;
};

class JToolBar
{
public:
    int _toolBarNo;
    QString _toolBarTitle;
    QSize _IconSize;
    int _textStyle;//BarItemSytle
    int _count_ToolBarItemLst;
    QList<BarItem*> _toolBarItemList;
};

class viewConfigModel:public QObject
{
    Q_OBJECT
public:
    viewConfigModel(QObject* parent);
    virtual ~viewConfigModel();

    viewConfigModel& operator=(const viewConfigModel &other);

    friend QDataStream& operator>>(QDataStream&, viewConfigModel&);
    friend QDataStream& operator<<(QDataStream&, viewConfigModel&);
    friend int JTreeCopy(JMenuNode* tn1, JMenuNode* tn2);
    friend QDataStream& JTreeFromBnr(QDataStream& src, JMenuNode* tn);
    friend QDataStream& JTreeToBnr(QDataStream& src, JMenuNode* tn);

public:
    void resetData();
    viewConfigModel* _this;
    bool _isEnable_ShowMenu = true;
    bool _isEnable_ShowToolbar = true;
    bool _isEnable_ShowStatusbar = true;
    bool _dock_Floatable = false;
    bool _dock_Moveable = false;
    bool _dock_Closeable = false;

    int _count_MenuTopItemLst=0;
    QList<JMenuNode*> _menuTopItemLst;

    int _count_ToolBarLst=0;
    QList<JToolBar*> _toolBarLst;

    int _count_StatusBarItemLst = 0;
    QList<StatusbarItem*> _statusBarItemLst;

    int _count_WorkSpaceWidgetLst = 0;
    QList<WidgetItem*> _workspaceWidgetLst;
};

#endif // QCFCONFIGMODEL_H
