/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "viewconfigmodel.h"
#include <QFile>
#include <QDataStream>

int JTreeCopy(JMenuNode *tn1, JMenuNode *tn2);
QDataStream& JTreeFromBnr(QDataStream& src, JMenuNode* tn);
QDataStream& JTreeToBnr(QDataStream& out, JMenuNode* tn);

viewConfigModel::viewConfigModel(QObject* parent){
    this->setParent(parent);
    _this = this;

    this->resetData();
}

viewConfigModel::~viewConfigModel(){
}

viewConfigModel& viewConfigModel::operator =(const viewConfigModel& other)
{
    _isEnable_ShowMenu = other._isEnable_ShowMenu;
    _isEnable_ShowToolbar = other._isEnable_ShowToolbar;
    _isEnable_ShowStatusbar = other._isEnable_ShowStatusbar;

    _count_MenuTopItemLst = other._count_MenuTopItemLst;
    for(int i=0; i<_count_MenuTopItemLst; i++)
        JTreeCopy(_menuTopItemLst[i], other._menuTopItemLst[i]);

    _count_ToolBarLst = other._count_ToolBarLst;
    for(int i=0; i<_count_ToolBarLst; i++)
    {
        _toolBarLst[i]->_toolBarNo = other. _toolBarLst[i]->_toolBarNo;
        _toolBarLst[i]->_count_ToolBarItemLst = other. _toolBarLst[i]->_count_ToolBarItemLst;
        for(int j=0; j<_toolBarLst[i]->_count_ToolBarItemLst; j++)
        {
            _toolBarLst[i]->_toolBarItemList[j]->_type = other._toolBarLst[i]->_toolBarItemList[j]->_type;

            if(_toolBarLst[i]->_toolBarItemList[j]->_type==TP_ACTION)
            {
                _toolBarLst[i]->_toolBarItemList[j]->_actionItem->_actionObjectName = other._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_actionObjectName;
                _toolBarLst[i]->_toolBarItemList[j]->_actionItem->_actionDetail = other._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_actionDetail;
                _toolBarLst[i]->_toolBarItemList[j]->_actionItem->_authority = other._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_authority;
                _toolBarLst[i]->_toolBarItemList[j]->_actionItem->_isEnable = other._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_isEnable;
                _toolBarLst[i]->_toolBarItemList[j]->_actionItem->_isVisible = other._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_isVisible;

                _toolBarLst[i]->_toolBarItemList[j]->_width = other._toolBarLst[i]->_toolBarItemList[j]->_width;
                _toolBarLst[i]->_toolBarItemList[j]->_height = other._toolBarLst[i]->_toolBarItemList[j]->_height;
            }
            else if(_toolBarLst[i]->_toolBarItemList[j]->_type==TP_WIDGET)
            {
                _toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginType = other._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginType;
                _toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginID = other._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginID;
                _toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_copyID = other._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_copyID;
                _toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetObjectName = other._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetObjectName;
                _toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetDetail = other._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetDetail;
                _toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_authority = other._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_authority;
                _toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_isEnable = other._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginType;
                _toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_isVisible = other._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_isEnable;
                _toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetOrigWidth = other._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetOrigWidth;
                _toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetOrigHeight = other._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetOrigHeight;

                _toolBarLst[i]->_toolBarItemList[j]->_width = other._toolBarLst[i]->_toolBarItemList[j]->_width;
                _toolBarLst[i]->_toolBarItemList[j]->_height = other._toolBarLst[i]->_toolBarItemList[j]->_height;
            }
        }
    }

    _count_StatusBarItemLst = other._count_StatusBarItemLst;
    for(int i=0; i<_count_StatusBarItemLst; i++)
    {
        _statusBarItemLst[i]->_pluginType = other._statusBarItemLst[i]->_pluginType;
        _statusBarItemLst[i]->_pluginID = other._statusBarItemLst[i]->_pluginID;
        _statusBarItemLst[i]->_copyID = other._statusBarItemLst[i]->_copyID;
        _statusBarItemLst[i]->_widgetObjectName = other._statusBarItemLst[i]->_widgetObjectName;
        _statusBarItemLst[i]->_widgetDetail = other._statusBarItemLst[i]->_widgetDetail;
        _statusBarItemLst[i]->_authority = other._statusBarItemLst[i]->_authority;
        _statusBarItemLst[i]->_isEnable = other._statusBarItemLst[i]->_pluginType;
        _statusBarItemLst[i]->_isVisible = other._statusBarItemLst[i]->_isEnable;
        _statusBarItemLst[i]->_widgetOrigWidth = other._statusBarItemLst[i]->_widgetOrigWidth;
        _statusBarItemLst[i]->_widgetOrigHeight = other._statusBarItemLst[i]->_widgetOrigHeight;
    }

    _count_WorkSpaceWidgetLst = other._count_WorkSpaceWidgetLst;
    for(int i=0; i<_count_WorkSpaceWidgetLst; i++)
    {
        _workspaceWidgetLst[i]->_pluginType = other._workspaceWidgetLst[i]->_pluginType;
        _workspaceWidgetLst[i]->_pluginID = other._workspaceWidgetLst[i]->_pluginID;
        _workspaceWidgetLst[i]->_copyID = other._workspaceWidgetLst[i]->_copyID;
        _workspaceWidgetLst[i]->_widgetObjectName = other._workspaceWidgetLst[i]->_widgetObjectName;
        _workspaceWidgetLst[i]->_widgetDetail = other._workspaceWidgetLst[i]->_widgetDetail;
        _workspaceWidgetLst[i]->_authority = other._workspaceWidgetLst[i]->_authority;
        _workspaceWidgetLst[i]->_isEnable = other._workspaceWidgetLst[i]->_pluginType;
        _workspaceWidgetLst[i]->_isVisible = other._workspaceWidgetLst[i]->_isEnable;
        _workspaceWidgetLst[i]->_widgetOrigWidth = other._workspaceWidgetLst[i]->_widgetOrigWidth;
        _workspaceWidgetLst[i]->_widgetOrigHeight = other._workspaceWidgetLst[i]->_widgetOrigHeight;
    }

    return *this;
}

QDataStream& operator>>(QDataStream& src, viewConfigModel& data)
{
    /*
     错误:C2679: 二进制“>>”: 没有找到接受“quint32”类型的右操作数的运算
    解决方法：因为没有添加头文件<QDataStream>
    */
    src >> data._isEnable_ShowMenu;
    src >> data._isEnable_ShowToolbar;
    src >> data._isEnable_ShowStatusbar;

    src >> data._count_MenuTopItemLst;

    for(int i=0; i<data._count_MenuTopItemLst; i++)
    {
        JMenuNode *tNode = new JMenuNode();
        data._menuTopItemLst.append(tNode);
        JTreeFromBnr(src, tNode);
    }

    src >> data._count_ToolBarLst;
    for(int i=0; i<data._count_ToolBarLst; i++)
    {
        JToolBar* tToolbar = new JToolBar();
        data._toolBarLst.append(tToolbar);

        src >> tToolbar->_toolBarNo;
        src >> tToolbar->_count_ToolBarItemLst;
        for(int j=0; j<tToolbar->_count_ToolBarItemLst; j++)
        {
            BarItem* tItem = new BarItem();
            tToolbar->_toolBarItemList.append(tItem);

            src >> tItem->_type;

            if(tItem->_type == TP_ACTION)
            {
                ActionItem* tActionItem = new ActionItem();
                tItem->_actionItem = tActionItem;
                src >> tActionItem->_actionObjectName;
                src >> tActionItem->_actionDetail;
                src >> tActionItem->_authority;
                src >> tActionItem->_isEnable;
                src >> tActionItem->_isVisible;

                src >> tItem->_width;
                src >> tItem->_height;
            }

            if(tItem->_type == TP_WIDGET)
            {
                WidgetItem* tWidgetItem = new WidgetItem();
                tItem->_widgetItem = tWidgetItem;

                src >> tWidgetItem->_pluginType;
                src >> tWidgetItem->_pluginID;
                src >> tWidgetItem->_copyID;
                src >> tWidgetItem->_widgetObjectName;
                src >> tWidgetItem->_widgetDetail;
                src >> tWidgetItem->_authority;
                src >> tWidgetItem->_isEnable;
                src >> tWidgetItem->_isVisible;
                src >> tWidgetItem->_widgetOrigWidth;
                src >> tWidgetItem->_widgetOrigHeight;

                src >> tItem->_width;
                src >> tItem->_height;
            }
        }
    }

    src >> data._count_StatusBarItemLst;
    for(int i=0; i<data._count_StatusBarItemLst; i++)
    {
        WidgetItem* tItem = new WidgetItem();
        data._statusBarItemLst.append(tItem);

        src >> tItem->_pluginType;
        src >> tItem->_pluginID;
        src >> tItem->_copyID;
        src >> tItem->_widgetObjectName;
        src >> tItem->_widgetDetail;
        src >> tItem->_authority;
        src >> tItem->_isEnable;
        src >> tItem->_isVisible;
        src >> tItem->_widgetOrigWidth;
        src >> tItem->_widgetOrigHeight;
    }

    src >> data._count_WorkSpaceWidgetLst;
    for(int i=0; i<data._count_WorkSpaceWidgetLst; i++)
    {
        WidgetItem* tItem = new WidgetItem();
        data._workspaceWidgetLst.append(tItem);

        src >> tItem->_pluginType;
        src >> tItem->_pluginID;
        src >> tItem->_copyID;
        src >> tItem->_widgetObjectName;
        src >> tItem->_widgetDetail;
        src >> tItem->_authority;
        src >> tItem->_isEnable;
        src >> tItem->_isVisible;
        src >> tItem->_widgetOrigWidth;
        src >> tItem->_widgetOrigHeight;
    }
    return src;
}

QDataStream& operator<<(QDataStream& out, viewConfigModel& data)
{
    out << data._isEnable_ShowMenu;
    out << data._isEnable_ShowToolbar;
    out << data._isEnable_ShowStatusbar;

    out << data._count_MenuTopItemLst;
    for(int i=0; i<data._count_MenuTopItemLst; i++)
        JTreeToBnr(out, data._menuTopItemLst[i]);

    out << data._count_ToolBarLst;
    for(int i=0; i<data._count_ToolBarLst; i++)
    {
        out << data._toolBarLst[i]->_toolBarNo;
        out << data._toolBarLst[i]->_count_ToolBarItemLst;

        for(int j=0; j<data._toolBarLst[i]->_count_ToolBarItemLst; j++)
        {
            out << data._toolBarLst[i]->_toolBarItemList[j]->_type;

            if(data._toolBarLst[i]->_toolBarItemList[j]->_type==TP_ACTION)
            {
                out << data._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_actionObjectName;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_actionDetail;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_authority;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_isEnable;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_isVisible;

                out << data._toolBarLst[i]->_toolBarItemList[j]->_width;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_height;
            }

            if(data._toolBarLst[i]->_toolBarItemList[j]->_type==TP_WIDGET)
            {
                out << data._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginType;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginID;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_copyID;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetObjectName;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetDetail;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_authority;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_isEnable;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_isVisible;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetOrigWidth;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetOrigHeight;

                out << data._toolBarLst[i]->_toolBarItemList[j]->_width;
                out << data._toolBarLst[i]->_toolBarItemList[j]->_height;
            }
        }
    }

    out << data._count_StatusBarItemLst;
    for(int i=0; i<data._count_StatusBarItemLst; i++)
    {
        out << data._statusBarItemLst[i]->_pluginType;
        out << data._statusBarItemLst[i]->_pluginID;
        out << data._statusBarItemLst[i]->_copyID;
        out << data._statusBarItemLst[i]->_widgetObjectName;
        out << data._statusBarItemLst[i]->_widgetDetail;
        out << data._statusBarItemLst[i]->_authority;
        out << data._statusBarItemLst[i]->_isEnable;
        out << data._statusBarItemLst[i]->_isVisible;
        out << data._statusBarItemLst[i]->_widgetOrigWidth;
        out << data._statusBarItemLst[i]->_widgetOrigHeight;
    }

    out << data._count_WorkSpaceWidgetLst;
    for(int i=0; i<data._count_WorkSpaceWidgetLst; i++)
    {
        out << data._workspaceWidgetLst[i]->_pluginType;
        out << data._workspaceWidgetLst[i]->_pluginID;
        out << data._workspaceWidgetLst[i]->_copyID;
        out << data._workspaceWidgetLst[i]->_widgetObjectName;
        out << data._workspaceWidgetLst[i]->_widgetDetail;
        out << data._workspaceWidgetLst[i]->_authority;
        out << data._workspaceWidgetLst[i]->_isEnable;
        out << data._workspaceWidgetLst[i]->_isVisible;
        out << data._workspaceWidgetLst[i]->_widgetOrigWidth;
        out << data._workspaceWidgetLst[i]->_widgetOrigHeight;
    }

    return out;
}

int JTreeCopy(JMenuNode *t1, JMenuNode *t2)
{
    if(t1->_children.count()!=t2->_children.count())
        return -1;

    for(int i=0; i<t1->_children.count(); i++)
    {
        if(t1->_children[i]->_children.count()>0)
            JTreeCopy(t1->_children[i], t2->_children[i]);
        t1->_children[i] = t2->_children[i];
    }
}

QDataStream& JTreeFromBnr(QDataStream& src, JMenuNode* tn)
{
    src >> tn->_menuTitle;
    src >> tn->_menuShortCut;
    src >> tn->_menuIconPath;
    src >> tn->_menuAuthority;
    src >> tn->_menuIsEnable;
    src >> tn->_menuIsVisible;
    src >> tn->_menuCheckable;
    src >> tn->_menuIsSeprator;

    src >> tn->_pluginType;
    src >> tn->_pluginID;
    src >> tn->_copyID;

    src >> tn->_functionName;
    src >> tn->_functionDetail;

    src >> tn->_parentMenuTitle;

    src >> tn->_count_children;
    for(int i=0; i<tn->_count_children; i++)
    {
        JMenuNode* tNode = new JMenuNode();
        tn->_children.append(tNode);
        JTreeFromBnr(src, tNode);
    }
    return src;
}

QDataStream& JTreeToBnr(QDataStream& out, JMenuNode* tn)
{
    out << tn->_menuTitle;
    out << tn->_menuShortCut;
    out << tn->_menuIconPath;
    out << tn->_menuAuthority;
    out << tn->_menuIsEnable;
    out << tn->_menuIsVisible;
    out << tn->_menuCheckable;
    out << tn->_menuIsSeprator;

    out << tn->_pluginType;
    out << tn->_pluginID;
    out <<  tn->_copyID;

    out << tn->_functionName;
    out << tn->_functionDetail;

    out << tn->_parentMenuTitle;

    out << tn->_count_children;
    for(int i=0; i<tn->_count_children; i++)
        JTreeToBnr(out, tn->_children[i]);

    return out;
}

void viewConfigModel::resetData()
{
    _isEnable_ShowMenu = false;
    _isEnable_ShowToolbar = false;
    _isEnable_ShowStatusbar = false;
    _count_MenuTopItemLst = 0;
    _menuTopItemLst.clear();
    _count_ToolBarLst = 0;
    _toolBarLst.clear();
    _count_StatusBarItemLst=0;
    _statusBarItemLst.clear();
    _count_WorkSpaceWidgetLst = 0;
    _workspaceWidgetLst.clear();
}

