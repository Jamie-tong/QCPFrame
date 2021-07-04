/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "ViewEditor.h"
#include "ui_ViewEditor.h"

#include "../../../interface/plugininterface.h"
#include <QTimer>
#include <QStringLiteral>
#include <QMessageBox>
#include "PluginActionViewer.h"
#include "PluginWidgetViewer.h"
#include <QFileDialog>
#include "utility/ccheckboxheaderview.h"
#include "PluginIO.h"

#define CONST_STR_SYSTEM  "System"
#define CONST_STR_NONSYSTEM        "NonSystem"
#define CONST_STR_SEPARATOR  "[-----------------]"
#define CONST_STR_SPACER        "<--------------->"

#define CONST_STR_NO_TEXT      "No Text"
#define CONST_STR_TEXT_BESIDE_ICON      "Text Beside Icon"
#define CONST_STR_TEXT_UNDER_ICON      "Text Under Icon"

#define CONST_STR_STATUSITEM_COMMON      "Common"
#define CONST_STR_STATUSITEM_PERMANENT      "Permanent"

#define CONST_STR_ITEMTYPE_ACTION      "Action"
#define CONST_STR_ITEMTYPE_SEPARATOR      "Separator"
#define CONST_STR_ITEMTYPE_WIDGET      "Widget"
#define CONST_STR_ITEMTYPE_SPACER      "Spacer"



ViewEditor* pViewEdInstance;

ViewEditor::ViewEditor(QWidget *parent) :
    QDialog(parent),ui(new Ui::ViewEditor)
{
    ui->setupUi(this);

    this->setParent(parent);

    pViewEdInstance = this;
    pluginInst = PluginIO::getInstance();
    _view = (QCPF_ViewModel*)pluginInst->_core->_view;
    connect(this,SIGNAL(sig_SelAllOrNot(bool)),this,SLOT(slot_SelAllOrNot(bool)));

    setWindowFlags(Qt::Dialog
                   | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    setMinimumSize(QSize(1024, 790));
    setSizeGripEnabled(true);

    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnULoaded()));

    ui->btnOk->setFocus();
    ui->btnOk->setDefault(true);

    QTreeWidget* _currentTree = nullptr;
    QTreeWidgetItem* _currentItem_TreeMenuEdit = nullptr;
    QTableWidget* _currentTable = nullptr;
    QTableWidgetItem* _currentItem_tableStatusbarEditer = nullptr;
}

ViewEditor::~ViewEditor()
{

}

void ViewEditor::resizeEvent(QResizeEvent *event)
{
    if(!_isFirstResize)
        return;
    else
        _isFirstResize = false;
}

void ViewEditor::showEvent(QShowEvent *event)
{
    _timer->start(1);
}

void ViewEditor::slot_OnULoaded()
{
    setConfigToUI();
    ui->treeMenuEdit->expandAll();
}

int getTreeElement(QTreeWidgetItem* root)
{
    for(int i=0; i<root->childCount(); i++)
    {
        root->child(i)->text(0);
    }

    return 0;
}

int getConfigFromChildNode(QTreeWidgetItem* treeTopNode, JMenuNode* configParentNode)
{
    configParentNode->_menuTitle = treeTopNode->text(0);
    configParentNode->_menuIsSeprator = treeTopNode->text(0)==CONST_STR_SEPARATOR?true:false;
    configParentNode->_menuShortCut = treeTopNode->text(1);
    configParentNode->_menuIconPath = treeTopNode->text(2);
    configParentNode->_menuAuthority = treeTopNode->text(3).toInt();
    configParentNode->_menuCheckable = treeTopNode->text(4)=="True"?true:false;

    QString tt = treeTopNode->text(5);

    configParentNode->_pluginType = treeTopNode->text(5)==CONST_STR_SYSTEM?0:1;
    configParentNode->_pluginID = treeTopNode->text(6);
    configParentNode->_copyID = treeTopNode->text(7);
    configParentNode->_actionName = treeTopNode->text(8);
    configParentNode->_actionDetail = treeTopNode->text(9);

    configParentNode->_count_children = treeTopNode->childCount();
    for(int i=0; i<configParentNode->_count_children; i++)
    {
        JMenuNode* configChildNode = new JMenuNode();

        configChildNode->_parentMenuTitle = treeTopNode->text(0);
        configParentNode->_children.append(configChildNode);
        getConfigFromChildNode(treeTopNode->child(i), configChildNode);
    }

    return 0;
}

 int ViewEditor::getConfigFromUI()
 {
    _view->_config._menuTopItemLst.clear();
    _view->_config._isEnable_ShowMenu = ui->chb_IsShowMenu->isChecked();
    _view->_config._isEnable_ShowToolbar = ui->chb_IsShowToolBar->isChecked();
    _view->_config._isEnable_ShowStatusbar = ui->chb_IsShowStatusBar->isChecked();
    _view->_config._dock_Floatable = ui->chb_DockFloatable->isChecked();
    _view->_config._dock_Moveable = ui->chb_DockMoveable->isChecked();
    _view->_config._dock_Closeable = ui->chb_DockCloseable->isChecked();

    _view->_config._count_MenuTopItemLst = ui->treeMenuEdit->topLevelItemCount();
    _view->_config._menuTopItemLst.clear();
    for(int i=0; i<_view->_config._count_MenuTopItemLst; i++)
    {
        JMenuNode* topJMenuNode = new JMenuNode();
        _view->_config._menuTopItemLst.append(topJMenuNode);
        topJMenuNode->_parentMenuTitle = "";
        getConfigFromChildNode(ui->treeMenuEdit->topLevelItem(i), topJMenuNode);
    }

    _view->_config._count_ToolBarLst = ui->treeToolbarEdit->topLevelItemCount();
    _view->_config._toolBarLst.clear();
    for(int i=0; i<_view->_config._count_ToolBarLst; i++)
    {
        JToolBar* tToolbar = new JToolBar();
        _view->_config._toolBarLst.append(tToolbar);

        tToolbar->_toolBarNo = i;
        tToolbar->_toolBarTitle = ui->treeToolbarEdit->topLevelItem(i)->text(0);
        tToolbar->_IconSize = QSize(ui->treeToolbarEdit->topLevelItem(i)->text(3).toInt(), ui->treeToolbarEdit->topLevelItem(i)->text(4).toInt());

        if(ui->treeToolbarEdit->topLevelItem(i)->text(2) == CONST_STR_NO_TEXT)
            tToolbar->_textStyle = BarItemSytle::BS_NO_TEXT;
        else if(ui->treeToolbarEdit->topLevelItem(i)->text(2) == CONST_STR_TEXT_BESIDE_ICON)
            tToolbar->_textStyle = BarItemSytle::BS_TEXT_BESIDE_ICON;
        else if(ui->treeToolbarEdit->topLevelItem(i)->text(2) == CONST_STR_TEXT_UNDER_ICON)
            tToolbar->_textStyle = BarItemSytle::BS_TEXT_UNDER_ICON;

        tToolbar->_count_ToolBarItemLst = ui->treeToolbarEdit->topLevelItem(i)->childCount();
        tToolbar->_toolBarItemList.clear();
        for(int j=0; j<tToolbar->_count_ToolBarItemLst; j++)
        {
            BarItem* tItem = new BarItem();
            tToolbar->_toolBarItemList.append(tItem);

            QString tTypeStr = ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(1);

            if(tTypeStr.compare(CONST_STR_ITEMTYPE_ACTION)==0)
                tItem->_type = BT_ACTION;
            else if(tTypeStr.compare(CONST_STR_ITEMTYPE_WIDGET)==0)
                tItem->_type = BT_WIDGET;
            else if(tTypeStr.compare(CONST_STR_ITEMTYPE_SEPARATOR)==0)
                tItem->_type = BT_SEPARATOR;
            else if(tTypeStr.compare(CONST_STR_ITEMTYPE_SPACER)==0)
                tItem->_type = BT_SPACER;

            if(tItem->_type==BT_ACTION)
            {
                ActionItem* tActionItem = new ActionItem();
                tItem->_actionItem = tActionItem;

                tActionItem->_actionObjectName = ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(0);

                tItem->_width = ui->treeToolbarEdit->topLevelItem(i)->text(3).toInt();
                tItem->_height = ui->treeToolbarEdit->topLevelItem(i)->text(4).toInt();
            }
            else if(tItem->_type==BT_WIDGET)
            {
                WidgetItem* tWidgetItem = new WidgetItem();
                tItem->_widgetItem = tWidgetItem;

                QStringList splitStrLst =  ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(0).split(";");
                if(splitStrLst.count()!=4)
                    return -1;

                tWidgetItem->_widgetObjectName = splitStrLst[0];
                if(splitStrLst[1] == tr(CONST_STR_SYSTEM))
                    tWidgetItem->_pluginType = 0;
                else if(splitStrLst[1] == tr(CONST_STR_NONSYSTEM))
                    tWidgetItem->_pluginType = 1;

                tWidgetItem->_pluginID = splitStrLst[2];
                tWidgetItem->_copyID = splitStrLst[3];


                tWidgetItem->_widgetOrigWidth = ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(3).toInt();
                tWidgetItem->_widgetOrigHeight = ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(4).toInt();

                tItem->_width = tWidgetItem->_widgetOrigWidth;
                tItem->_height = tWidgetItem->_widgetOrigHeight;
            }

        }
    }

    _view->_config._count_StatusBarItemLst = ui->tableStatusbarEditer->rowCount();
    _view->_config._statusBarItemLst.clear();
    for(int i=0; i<_view->_config._count_StatusBarItemLst; i++)
    {
        StatusbarItem* tStatusbarItem = new StatusbarItem();
        _view->_config._statusBarItemLst.append(tStatusbarItem);

        QStringList splitStrLst =  ui->tableStatusbarEditer->item(i, 1)->text().split(tr(";"));
        if(splitStrLst.count()!=4)
            return -1;

        tStatusbarItem->_widgetObjectName = splitStrLst[0];
        if(splitStrLst[1] == CONST_STR_SYSTEM)
            tStatusbarItem->_pluginType = PT_SYS;
        else if(splitStrLst[1] == CONST_STR_NONSYSTEM)
            tStatusbarItem->_pluginType = PT_NON_SYS;

        tStatusbarItem->_pluginID = splitStrLst[2];
        tStatusbarItem->_copyID = splitStrLst[3];

        tStatusbarItem->_statusbarItemType = ui->tableStatusbarEditer->item(i, 2)->text()==CONST_STR_STATUSITEM_COMMON?SBT_COMMON:SBT_PERMANENT;
        tStatusbarItem->_widgetOrigWidth = ui->tableStatusbarEditer->item(i, 3)->text().toInt();
        tStatusbarItem->_widgetOrigHeight = ui->tableStatusbarEditer->item(i, 4)->text().toInt();
    }

    _view->_config._count_WorkSpaceWidgetLst = ui->tablePluginWidget->rowCount();
    _view->_config._workspaceWidgetLst.clear();
    for(int i=0; i<_view->_config._count_WorkSpaceWidgetLst; i++)
    {
        WidgetItem* tWidgetItem = new WidgetItem();
        _view->_config._workspaceWidgetLst.append(tWidgetItem);

        Qt::CheckState tState = ui->tablePluginWidget->item(i, 0)->checkState();
        if(tState == Qt::CheckState::Checked)
            tWidgetItem->_isVisible = true;
        else
            tWidgetItem->_isVisible = false;

        tWidgetItem->_widgetObjectName = ui->tablePluginWidget->item(i, 2)->text();

        if(ui->tablePluginWidget->item(i, 3)->text()==CONST_STR_SYSTEM)
            tWidgetItem->_pluginType = PT_SYS;
        else if(ui->tablePluginWidget->item(i, 3)->text()==CONST_STR_NONSYSTEM)
            tWidgetItem->_pluginType = PT_NON_SYS;

        tWidgetItem->_pluginID = ui->tablePluginWidget->item(i, 4)->text();
        tWidgetItem->_copyID = ui->tablePluginWidget->item(i, 5)->text();
    }
     return 0;
 }

 void parseNodeToTree(JMenuNode* configNode, QTreeWidgetItem* treeNode, QComboBox* cbToolbarAction)
 {
    if(configNode->_children.count()==0)
    {
        QTreeWidgetItem* treeChildNode = new QTreeWidgetItem();
        treeNode->addChild(treeChildNode);

        treeChildNode->setText(0, configNode->_menuTitle);

         if(configNode->_menuTitle != CONST_STR_SEPARATOR)
         {
             treeChildNode->setText(1, configNode->_menuShortCut);
             treeChildNode->setText(2, configNode->_menuIconPath);

             QString finalIconPath;
             if(QFile::exists(configNode->_menuIconPath))
                 finalIconPath = configNode->_menuIconPath;
             else
             {
                 QFileInfo fInfo(configNode->_menuIconPath);
                 QString tFileName = fInfo.fileName();
                 if(QFile::exists(PluginIO::getInstance()->_core->I_ApplicationDirPath + "/Images/" + tFileName))
                     finalIconPath = PluginIO::getInstance()->_core->I_ApplicationDirPath + "/Images/" + tFileName;
             }
            treeChildNode->setIcon(0, QIcon(finalIconPath));
            treeChildNode->setText(3, QString::number(configNode->_menuAuthority));
            treeChildNode->setText(4, configNode->_menuCheckable?QStringLiteral("True"):QStringLiteral("False"));


               treeChildNode->setText(5, configNode->_pluginType?CONST_STR_NONSYSTEM:CONST_STR_SYSTEM);
               treeChildNode->setText(6, configNode->_pluginID);
               treeChildNode->setText(7, configNode->_copyID);
               treeChildNode->setText(8, configNode->_actionName);
               treeChildNode->setText(9, configNode->_actionDetail);

               if(configNode->_actionName!="" && cbToolbarAction->findText(configNode->_actionName)<0)
               {
                   cbToolbarAction->addItem(treeChildNode->icon(0), configNode->_actionName);
               }

         }
    }
    else
    {
        QString tStr = configNode->_parentMenuTitle;
        if(configNode->_parentMenuTitle =="")
        {
            for(int i=0; i<configNode->_children.count(); i++)
            {
                parseNodeToTree(configNode->_children[i], treeNode, cbToolbarAction);
            }
        }
        else
        {
            QTreeWidgetItem* treeHasChildNode = new QTreeWidgetItem();
            treeNode->addChild(treeHasChildNode);

            treeHasChildNode->setText(0, configNode->_menuTitle);
            treeHasChildNode->setText(1, configNode->_menuShortCut);
            treeHasChildNode->setText(2, configNode->_menuIconPath);

            QString finalIconPath;
            if(QFile::exists(configNode->_menuIconPath))
                finalIconPath = configNode->_menuIconPath;
            else
            {
                QFileInfo fInfo(configNode->_menuIconPath);
                QString tFileName = fInfo.fileName();
                if(QFile::exists(PluginIO::getInstance()->_core->I_ApplicationDirPath + "/Images/" + tFileName))
                    finalIconPath = PluginIO::getInstance()->_core->I_ApplicationDirPath + "/Images/" + tFileName;
            }
           treeHasChildNode->setIcon(0, QIcon(finalIconPath));
           treeHasChildNode->setText(3, QString::number(configNode->_menuAuthority));
           treeHasChildNode->setText(4, configNode->_menuCheckable?QStringLiteral("True"):QStringLiteral("False"));

            for(int i=0; i<configNode->_children.count(); i++)
            {
                parseNodeToTree(configNode->_children[i], treeHasChildNode, cbToolbarAction);
            }
        }
    }
 }

 int ViewEditor::setConfigToUI()
 {
     ui->tabWidget->setCurrentIndex(0);
     ui->chb_IsShowMenu->setChecked(_view->_config._isEnable_ShowMenu);
     ui->chb_IsShowToolBar->setChecked(_view->_config._isEnable_ShowToolbar);
     ui->chb_IsShowStatusBar->setChecked(_view->_config._isEnable_ShowStatusbar);

     ui->chb_DockFloatable->setChecked(_view->_config._dock_Floatable);
     ui->chb_DockMoveable->setChecked(_view->_config._dock_Moveable);
     ui->chb_DockCloseable->setChecked(_view->_config._dock_Closeable);

     ui->treeMenuEdit->setColumnCount(10);
     QStringList nHeadLst;
     nHeadLst.clear();
     nHeadLst<<tr("Menu")<<tr("Shortcut")<<tr("Icon Path")<<tr("Authority")<<tr("Checkable")<<tr("Plugin Type")<<tr("Original Plugin ID")<<tr("Clone Plugin ID")<<tr("Action")<<("Detail");
     ui->treeMenuEdit->setHeaderLabels(nHeadLst);
     ui->treeMenuEdit->header()->setVisible(true);

     ui->treeMenuEdit->setColumnWidth(0, 180);
     ui->treeMenuEdit->setColumnWidth(1, 90);
     ui->treeMenuEdit->setColumnWidth(2, 110);
     ui->treeMenuEdit->setColumnWidth(3, 80);
     ui->treeMenuEdit->setColumnWidth(4, 80);
     ui->treeMenuEdit->setColumnWidth(5, 90);
     ui->treeMenuEdit->setColumnWidth(6, 120);
     ui->treeMenuEdit->setColumnWidth(7, 120);
     ui->treeMenuEdit->setColumnWidth(8, 110);
     ui->treeMenuEdit->setColumnWidth(9, 80);

     ui->treeMenuEdit->header()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
     ui->treeMenuEdit->header()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter); //居中
     ui->treeMenuEdit->header()->setStretchLastSection(true);
     ui->treeMenuEdit->setStyleSheet( "QTreeView::item:hover{background-color:rgb(110,178,233); color:white}"
     "QTreeView::item:selected{background-color:rgb(0,120,215)}"
     "QTreeView::item:selected{color: white}"
     "QTreeWidget::item{border-right: 1px solid silver; font:9pt '微软雅黑';}"
      );

    ui->treeMenuEdit->clear();
    ui->cbActionFromMenu_Toolbar->clear();
    for(int i=0; i<_view->_config._menuTopItemLst.count(); i++)
    {
        JMenuNode* tTopConfigNode = _view->_config._menuTopItemLst[i];
        QTreeWidgetItem* tTopTreeItem = new QTreeWidgetItem();

        tTopTreeItem->setText(0, tTopConfigNode->_menuTitle);
        tTopTreeItem->setText(1, tTopConfigNode->_menuShortCut);
        tTopTreeItem->setText(2, tTopConfigNode->_menuIconPath);
        tTopTreeItem->setText(3, QString::number(tTopConfigNode->_menuAuthority));
        tTopTreeItem->setText(4, tTopConfigNode->_menuCheckable?tr("True"):tr("False"));

        ui->treeMenuEdit->addTopLevelItem(tTopTreeItem);

        parseNodeToTree(tTopConfigNode, tTopTreeItem, ui->cbActionFromMenu_Toolbar);
    }
    ui->treeMenuEdit->expandAll();

    ui->treeToolbarEdit->setColumnCount(5);

    nHeadLst.clear();
    nHeadLst<<tr("Item")<<tr("Type")<<tr("Alignment")<<tr("Width")<<tr("Height");
    ui->treeToolbarEdit->setHeaderLabels(nHeadLst);
    ui->treeToolbarEdit->header()->setVisible(true);

    ui->treeToolbarEdit->setColumnWidth(0, 200);
    ui->treeToolbarEdit->setColumnWidth(1, 70);
    ui->treeToolbarEdit->setColumnWidth(2, 110);
    ui->treeToolbarEdit->setColumnWidth(3, 50);
    ui->treeToolbarEdit->setColumnWidth(4, 50);

    ui->treeToolbarEdit->header()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
    ui->treeToolbarEdit->header()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter); //居中
    ui->treeToolbarEdit->header()->setStretchLastSection(true);
    ui->treeToolbarEdit->setStyleSheet( "QTreeView::item:hover{background-color:rgb(110,178,233); color:white}"
    "QTreeView::item:selected{background-color:rgb(0,120,215)}"
    "QTreeView::item:selected{color: white}"
    "QTreeWidget::item{border-right: 1px solid silver; font:9pt '微软雅黑';}"
     );

    ui->treeToolbarEdit->clear();

    foreach (JToolBar* bar, _view->_config._toolBarLst) {
        QTreeWidgetItem* tTopTreeNode = new QTreeWidgetItem();
        tTopTreeNode->setText(0, bar->_toolBarTitle);
        switch(bar->_textStyle)
        {
            case BarItemSytle::BS_NO_TEXT:
                tTopTreeNode->setText(2, tr(CONST_STR_NO_TEXT));
                break;
            case BarItemSytle::BS_TEXT_BESIDE_ICON:
                tTopTreeNode->setText(2, tr(CONST_STR_TEXT_BESIDE_ICON));
                break;
            case BarItemSytle::BS_TEXT_UNDER_ICON:
                tTopTreeNode->setText(2, tr(CONST_STR_TEXT_UNDER_ICON));
                break;
        }
        tTopTreeNode->setText(3, QString::number(bar->_IconSize.width()));
        tTopTreeNode->setText(4, QString::number(bar->_IconSize.height()));

        ui->treeToolbarEdit->addTopLevelItem(tTopTreeNode);

        foreach (BarItem* item, bar->_toolBarItemList) {
            QTreeWidgetItem* tItemTreeNode = new QTreeWidgetItem();
            tTopTreeNode->addChild(tItemTreeNode);

            if(item->_type == BT_ACTION)
            {
                QIcon tIcon;
                foreach(QAction* act, _view->_actionList)
                {
                    if(act->objectName()==item->_actionItem->_actionObjectName)
                    {
                        tIcon = act->icon();
                        break;
                    }
                }
                tItemTreeNode->setIcon(0, tIcon);

                tItemTreeNode->setText(0, item->_actionItem->_actionObjectName);
                tItemTreeNode->setText(1, tr(CONST_STR_ITEMTYPE_ACTION));
            }
            else if(item->_type == BT_WIDGET)
            {
                QString pluginType = item->_widgetItem->_pluginType==PT_SYS?tr(CONST_STR_SYSTEM):tr(CONST_STR_NONSYSTEM);
                QString _itemTag = item->_widgetItem->_widgetObjectName + ";" +  pluginType + ";" + item->_widgetItem->_pluginID + ";" + item->_widgetItem->_copyID;
                tItemTreeNode->setText(0,_itemTag);
                tItemTreeNode->setText(1, tr(CONST_STR_ITEMTYPE_WIDGET));
                tItemTreeNode->setText(3, QString::number(item->_widgetItem->_widgetOrigWidth));
                tItemTreeNode->setText(4, QString::number(item->_widgetItem->_widgetOrigHeight));
            }
            else if(item->_type == BT_SEPARATOR)
            {
                tItemTreeNode->setText(0, tr(CONST_STR_SEPARATOR));
                tItemTreeNode->setText(1, tr(CONST_STR_ITEMTYPE_SEPARATOR));
            }
            else if(item->_type == BT_SPACER)
            {
                tItemTreeNode->setText(0, tr(CONST_STR_SPACER));
                tItemTreeNode->setText(1, tr(CONST_STR_ITEMTYPE_SPACER));
            }
        }
    }
    ui->treeToolbarEdit->expandAll();

    ui->tableStatusbarEditer->setColumnCount(5);
    ui->tableStatusbarEditer->setRowCount(0);

    ui->tableStatusbarEditer->clear();

    nHeadLst.clear();
    nHeadLst<<tr("No.")<<tr("Item")<<tr("Type")<<tr("Width")<<tr("Height");

    ui->tableStatusbarEditer->setHorizontalHeaderLabels(nHeadLst);

    ui->tableStatusbarEditer->setColumnWidth(0, 35);
    ui->tableStatusbarEditer->setColumnWidth(1, 150);
    ui->tableStatusbarEditer->setColumnWidth(2, 80);
    ui->tableStatusbarEditer->setColumnWidth(3, 50);
    ui->tableStatusbarEditer->setColumnWidth(4, 50);

    setTableStyle(ui->tableStatusbarEditer);

    int count = 0;
    foreach (StatusbarItem* item, _view->_config._statusBarItemLst) {
        int tRowCount = ui->tableStatusbarEditer->rowCount();
        ui->tableStatusbarEditer->insertRow(tRowCount);

        ui->tableStatusbarEditer->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(++count)));

        QString pluginType = item->_pluginType==PT_SYS?tr(CONST_STR_SYSTEM):tr(CONST_STR_NONSYSTEM);
        QString _itemTag = item->_widgetObjectName + ";" +  pluginType + ";" + item->_pluginID + ";" + item->_copyID;
        ui->tableStatusbarEditer->setItem(tRowCount, 1, new QTableWidgetItem(_itemTag));

        if(item->_statusbarItemType == StatusbarItemType::SBT_COMMON)
            ui->tableStatusbarEditer->setItem(tRowCount, 2, new QTableWidgetItem(tr(CONST_STR_STATUSITEM_COMMON)));
        else if(item->_statusbarItemType == StatusbarItemType::SBT_PERMANENT)
            ui->tableStatusbarEditer->setItem(tRowCount, 2, new QTableWidgetItem(tr(CONST_STR_STATUSITEM_PERMANENT)));

        ui->tableStatusbarEditer->setItem(tRowCount, 1, new QTableWidgetItem(_itemTag));
        ui->tableStatusbarEditer->setItem(tRowCount, 3, new QTableWidgetItem(QString::number(item->_widgetOrigWidth)));
        ui->tableStatusbarEditer->setItem(tRowCount, 4, new QTableWidgetItem(QString::number(item->_widgetOrigHeight)));
    }

    ui->tablePluginWidget->setColumnCount(8);
    ui->tablePluginWidget->setRowCount(0);

    ui->tablePluginWidget->clear();

    nHeadLst.clear();
    nHeadLst<<""<<tr("No.")<<tr("Widget")<<tr("Plugin Type")<<tr("Plugin ID")<<tr("Copy ID")<<tr("Is a Copy")<<tr("Widget Detail");

    CCheckBoxHeaderView *myHeader = new CCheckBoxHeaderView(0, Qt::Horizontal, ui->tablePluginWidget);
    ui->tablePluginWidget->setHorizontalHeader(myHeader);

    ui->tablePluginWidget->setHorizontalHeaderLabels(nHeadLst);

    ui->tablePluginWidget->setColumnWidth(0, 20);
    ui->tablePluginWidget->setColumnWidth(1, 100);
    ui->tablePluginWidget->setColumnWidth(2, 150);
    ui->tablePluginWidget->setColumnWidth(3, 150);
    ui->tablePluginWidget->setColumnWidth(4, 150);
    ui->tablePluginWidget->setColumnWidth(5, 80);
    ui->tablePluginWidget->setColumnWidth(6, 150);
    ui->tablePluginWidget->setColumnWidth(7, 200);

    setTableStyle(ui->tablePluginWidget);

    count = 0;

    foreach (Plugin_Interface* pi, ((QCPF_Interface*)_view->_core)->I_SysPlugins) {
        foreach (PluginWidgetInfo* pwi, pi->I_WidgetList) {

            bool isExist = false;
            bool isChecked = false;
            if(pwi->_showType != ST_DOCK)
                continue;
            foreach (WidgetItem* wi, _view->_config._workspaceWidgetLst) {
                if(wi->_pluginType == pi->I_PluginType &&
                   wi->_pluginID == pi->I_PluginID &&
                   wi->_copyID == pi->I_CopyID &&
                   wi->_widgetObjectName == pwi->_widget->objectName())
                {
                    isExist = true;
                    isChecked = wi->_isVisible;
                    break;
                }
            }

            int tRowCount = ui->tablePluginWidget->rowCount();
            ui->tablePluginWidget->insertRow(tRowCount);

            ui->tablePluginWidget->setItem(tRowCount, 0, new QTableWidgetItem(""));

            if(isExist)
                ui->tablePluginWidget->item(tRowCount, 0)->setCheckState(isChecked?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
            else
                ui->tablePluginWidget->item(tRowCount, 0)->setCheckState(Qt::CheckState::Unchecked);

            ui->tablePluginWidget->setItem(tRowCount, 1, new QTableWidgetItem(QString::number(++count)));
            ui->tablePluginWidget->setItem(tRowCount, 2, new QTableWidgetItem(pwi->_widget->objectName()));
            ui->tablePluginWidget->setItem(tRowCount, 3, new QTableWidgetItem(tr(CONST_STR_SYSTEM)));
            ui->tablePluginWidget->setItem(tRowCount, 4, new QTableWidgetItem(pi->I_PluginID));
            ui->tablePluginWidget->setItem(tRowCount, 5, new QTableWidgetItem(pi->I_CopyID));
            ui->tablePluginWidget->setItem(tRowCount, 6, new QTableWidgetItem(tr("No")));
            ui->tablePluginWidget->setItem(tRowCount, 7, new QTableWidgetItem(pwi->_widgetDetail));
        }
    }

    QList<Plugin_Interface*> tvec = ((QCPF_Interface*)_view->_core)->I_NSysAllValidPlugins;

    foreach (Plugin_Interface* pi, ((QCPF_Interface*)_view->_core)->I_NSysAllValidPlugins) {
        foreach (PluginWidgetInfo* pwi, pi->I_WidgetList) {

            bool isExist = false;
            bool isChecked = false;

            foreach (WidgetItem* wi, _view->_config._workspaceWidgetLst) {
                if(wi->_pluginType == pi->I_PluginType &&
                   wi->_pluginID == pi->I_PluginID &&
                   wi->_copyID == pi->I_CopyID &&
                   wi->_widgetObjectName == pwi->_widget->objectName())
                {
                    isExist = true;
                    isChecked = wi->_isVisible;
                    break;
                }
            }

            int tRowCount = ui->tablePluginWidget->rowCount();
            ui->tablePluginWidget->insertRow(tRowCount);

            ui->tablePluginWidget->setItem(tRowCount, 0, new QTableWidgetItem(""));

            if(isExist)
                ui->tablePluginWidget->item(tRowCount, 0)->setCheckState(isChecked?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
            else
                ui->tablePluginWidget->item(tRowCount, 0)->setCheckState(Qt::CheckState::Unchecked);

            ui->tablePluginWidget->setItem(tRowCount, 1, new QTableWidgetItem(QString::number(++count)));
            ui->tablePluginWidget->setItem(tRowCount, 2, new QTableWidgetItem(pwi->_widget->objectName()));
            ui->tablePluginWidget->setItem(tRowCount, 3, new QTableWidgetItem(tr(CONST_STR_NONSYSTEM)));
            ui->tablePluginWidget->setItem(tRowCount, 4, new QTableWidgetItem(pi->I_PluginID));
            ui->tablePluginWidget->setItem(tRowCount, 5, new QTableWidgetItem(pi->I_CopyID));
            ui->tablePluginWidget->setItem(tRowCount, 6, new QTableWidgetItem(pi->I_CopyID==""?tr("No"):tr("Yes")));
            ui->tablePluginWidget->setItem(tRowCount, 7, new QTableWidgetItem(pwi->_widgetDetail));
        }
    }
     return 0;
 }

 void ViewEditor::setTableStyle(QTableWidget *table)
 {
     table->horizontalHeader()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
     table->horizontalHeader()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter); //居左
     table->setAlternatingRowColors(true);
     table->verticalHeader()->setVisible(false);
     table->horizontalHeader()->setVisible(true);

     table->horizontalHeader()->setStretchLastSection(true);

     table->horizontalHeader()->setHighlightSections(false);
     table->setEditTriggers(QAbstractItemView::NoEditTriggers);
     table->setSelectionBehavior(QAbstractItemView::SelectRows);
     table->setSelectionMode( QAbstractItemView::SingleSelection);
     table->horizontalHeader()->setStretchLastSection(true);
     table->setStyleSheet("font:9pt '微软雅黑';");

     table->setSortingEnabled(false);
 }


 void ViewEditor::on_treeMenuEdit_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
 {
     if(previous!=nullptr && _currentCol_TreeMenuEdit>=0){
        ui->treeMenuEdit->removeItemWidget(previous, _currentCol_TreeMenuEdit);

        ui->treeMenuEdit->setStyleSheet( "QTreeView::item:hover{background-color:rgb(110,178,233); color:white}"
        "QTreeView::item:selected{background-color:rgb(0,120,215)}"
        "QTreeView::item:selected{color: white}"
        "QTreeWidget::item{border-right: 1px solid silver; font:9pt '微软雅黑';}"
         );
     }
 }

 void ViewEditor::on_treeToolbarEdit_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
 {
     if(previous!=nullptr && _currentCol_TreeMenuEdit>=0){
        ui->treeToolbarEdit->removeItemWidget(previous, _currentCol_TreeMenuEdit);

        ui->treeMenuEdit->setStyleSheet( "QTreeView::item:hover{background-color:rgb(110,178,233); color:white}"
        "QTreeView::item:selected{background-color:rgb(0,120,215)}"
        "QTreeView::item:selected{color: white}"
        "QTreeWidget::item{border-right: 1px solid silver; font:9pt '微软雅黑';}"
         );
     }
 }

 void ViewEditor::on_tableStatusbarEditer_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
 {
     if(previous!=nullptr && current!=nullptr){
        ui->tableStatusbarEditer->removeCellWidget(current->row(), current->column());
     }
 }

void ViewEditor::on_btnOk_clicked()
{
    getConfigFromUI();

    if(1==_view->slot_SaveConfigFile())
        QMessageBox::information(this, tr("information"), tr("View configuration has changed, please restart application for updating."));

    this->close();
}

void ViewEditor::on_btnCancel_clicked()
{
    _view->slot_CancelConfig();
    this->close();
}

void del(QTreeWidgetItem* node)
{
    if(node->childCount() > 0)
    {
        for(int i = 0; i < node->childCount(); i ++)
        {
            del(node->child(i));
        }
    }
    else
    {
        delete node;
    }
}

void ViewEditor::on_btnDeleteNode_clicked()
{
    QTreeWidgetItem* item = ui->treeMenuEdit->currentItem();
    if(item==nullptr)
        return;

    int tIndex = ui->cbActionFromMenu_Toolbar->findText(item->text(8));
    if(tIndex>=0)
        ui->cbActionFromMenu_Toolbar->removeItem(tIndex);

    if(item->childCount() > 0)
    {
        QMessageBox::StandardButton tBtn = QMessageBox::question(this, tr("Infomation"), tr("Are you sure to delete the item and it's children?"));
        if(tBtn==QMessageBox::No)
            return;
        for(int i = 0; i < item->childCount(); i ++)
        {
            del(item->child(i));
        }
    }
    delete item;
}

void ViewEditor::on_btnAddNode_clicked()
{
    if(ui->txtMenuTitle->text()=="")
    {
        QMessageBox::information(this, tr("Infomation"), tr("Node name can not be NULL!"));
        return;
    }

    QList<QTreeWidgetItem*> itemLst = ui->treeMenuEdit->findItems(ui->txtMenuTitle->text(), Qt::MatchFlag::MatchExactly);
    if(itemLst.count()>0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There are the same nodes in the tree!"));
        return;
    }

    QString tcut = ui->txtMenuShortcut->keySequence().toString();
    QList<QTreeWidgetItem*> shortcutLst = ui->treeMenuEdit->findItems(ui->txtMenuShortcut->keySequence().toString(), Qt::MatchFlag::MatchExactly, 1);
    if(shortcutLst.count()>0 && tcut!="")
    {
        QMessageBox::information(this, tr("Infomation"), tr("This shortcut has be used!"));
        return;
    }

    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, ui->txtMenuTitle->text());
    item->setText(1, ui->txtMenuShortcut->keySequence().toString());
    item->setText(3, QString::number(ui->cbMenuAuthority->currentIndex()));
    item->setText(4, ui->chkMenuCheckable->isChecked()?"True":"False");

    QTreeWidgetItem* curSelItem= ui->treeMenuEdit->currentItem();
    if(curSelItem==nullptr)
        ui->treeMenuEdit->addTopLevelItem(item);
    else
    {
        curSelItem->addChild(item);
        curSelItem->setExpanded(true);
    }

}

void ViewEditor::on_btnUp_clicked()
{
    TreeItemMoveUp(ui->treeMenuEdit);
}

void ViewEditor::on_btnDown_clicked()
{
    TreeItemMoveDown(ui->treeMenuEdit);
}

void ViewEditor::on_btnLeft_clicked()
{
    TreeItemMoveLeft(ui->treeMenuEdit);
}

void ViewEditor::on_btnRight_clicked()
{
    TreeItemMoveRight(ui->treeMenuEdit);
}

void ViewEditor::on_btnAddSeparator_clicked()
{
    QTreeWidgetItem* curSelItem= ui->treeMenuEdit->currentItem();
    if(curSelItem==nullptr || curSelItem->parent()==nullptr)
        return;
    else
    {
        QTreeWidgetItem* Separator = new QTreeWidgetItem();
        Separator->setText(0, tr(CONST_STR_SEPARATOR));
        curSelItem->parent()->addChild(Separator);
    }
}

void ViewEditor::on_btnLoadAction_clicked()
{
    if(ui->treeMenuEdit->selectedItems().count()==0)
        return;

    if(ui->treeMenuEdit->currentItem()->text(0)== CONST_STR_SEPARATOR)
        return;

    if(ui->treeMenuEdit->currentItem()->childCount()>0)
        return;

    PluginIO* plugInst = PluginIO::getInstance();
    PluginActionViewer* ce = new PluginActionViewer(plugInst->_core, ui->treeMenuEdit->currentItem(), this);
    ce->exec();

    if(ce->_isOk)
    {
        ui->treeMenuEdit->currentItem()->setText(5, ce->_pluginType);
        ui->treeMenuEdit->currentItem()->setText(6, ce->_pluginID);
        ui->treeMenuEdit->currentItem()->setText(7, ce->_copyID);
        ui->treeMenuEdit->currentItem()->setText(8, ce->_actionName);
        ui->treeMenuEdit->currentItem()->setText(9, ce->_actionDetail);

        int tActionIndex = ui->cbActionFromMenu_Toolbar->findText(ce->_actionName, Qt::MatchFlag::MatchExactly);
        if(tActionIndex>=0)
        {
            ui->cbActionFromMenu_Toolbar->setItemIcon(tActionIndex, ui->treeMenuEdit->currentItem()->icon(0));
            foreach(QAction* act,  _view->_actionList)
            {
                if(act->objectName() == ce->_actionName)
                {
                    act->setIcon(ui->treeMenuEdit->currentItem()->icon(0));
                    break;
                }
            }
            return;
        }
        else
        {
            ui->cbActionFromMenu_Toolbar->addItem(ui->treeMenuEdit->currentItem()->icon(0), ce->_actionName);
            _view->_actionList.append(new QAction(ui->treeMenuEdit->currentItem()->icon(0), ce->_actionName));
        }
    }
    delete  ce;
}


void ViewEditor::on_btnClearAction_clicked()
{
    QTreeWidgetItem* curSelItem= ui->treeMenuEdit->currentItem();

    if(curSelItem==nullptr)
        return;

    QString curActionName = curSelItem->text(8);

    int tIndex = ui->cbActionFromMenu_Toolbar->findText(curActionName);
    if(tIndex>=0)
        ui->cbActionFromMenu_Toolbar->removeItem(tIndex);

    foreach(QAction* act,  _view->_actionList)
    {
        if(act->objectName() == curActionName)
        {
            _view->_actionList.removeOne(act);
            break;
        }
    }

    for(int i=0; i<ui->treeToolbarEdit->topLevelItemCount(); i++) {
        bool isFinded = false;
        for(int j=0; j<ui->treeToolbarEdit->topLevelItem(i)->childCount(); j++){
            if(ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(1) == CONST_STR_ITEMTYPE_ACTION && ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(0) == curActionName)
            {
                isFinded = true;
                del(ui->treeToolbarEdit->topLevelItem(i)->child(j));
                ui->treeToolbarEdit->repaint();
            }
        }
        if(isFinded)
            break;
    }

    for(int i=5; i<ui->treeMenuEdit->columnCount(); i++)
        curSelItem->setText(i, "");
}

void ViewEditor::on_btnIconFinder_clicked()
{
    if(ui->treeMenuEdit->currentItem()==nullptr)
        return;

    if(ui->treeMenuEdit->currentItem()->text(0)== CONST_STR_SEPARATOR)
        return;

    QString file_name = QFileDialog::getOpenFileName(this,
            tr("Open Icon File"),
            PluginIO::getInstance()->_core->I_ApplicationDirPath,
            "Images (*.png *.jpg *.bmp *.icon)",
            0);
        if (!file_name.isNull())
        {
            QIcon tIcon =QIcon(file_name);

            ui->treeMenuEdit->currentItem()->setText(2, file_name);
            ui->treeMenuEdit->currentItem()->setIcon(0, tIcon);

            QString actionName = ui->treeMenuEdit->currentItem()->text(8);
            foreach(QAction* act, _view->_actionList)
            {
                if(act->text()==actionName)
                {
                    act->setIcon(tIcon);
                    break;
                }
            }

            int tCbIndex = ui->cbActionFromMenu_Toolbar->findText(actionName, Qt::MatchFlag::MatchExactly);
            ui->cbActionFromMenu_Toolbar->setItemIcon(tCbIndex, tIcon);

            QList<QTreeWidgetItem*> destItemsLst = ui->treeToolbarEdit->findItems(actionName, Qt::MatchFlag::MatchRecursive | Qt::MatchFlag::MatchExactly);
            foreach (QTreeWidgetItem* qwi, destItemsLst) {
                qwi->setIcon(0, tIcon);
            }
        }
}

void ViewEditor::on_btnAddAction_Toolbar_clicked()
{
    if(ui->treeToolbarEdit->topLevelItemCount()==0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is no toolbar node, Please add a bar first!"));
        return;
    }

    QTreeWidgetItem* tItem = ui->treeToolbarEdit->currentItem();
    if(tItem==nullptr)
    {
        QMessageBox::information(this, tr("Infomation"), tr("Please select the toolbar node!"));
        return;
    }

    QList<QTreeWidgetItem*> destItemsLst = ui->treeToolbarEdit->findItems(ui->cbActionFromMenu_Toolbar->currentText(), Qt::MatchFlag::MatchRecursive | Qt::MatchFlag::MatchExactly);
    if(destItemsLst.count()>0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is a same action existed!"));
        return;
    }

    //==========================================
    QTreeWidgetItem* rootItem;
    if(tItem->parent() == nullptr)
        rootItem = tItem;
    else
        rootItem = tItem->parent();

    QTreeWidgetItem* tChildItem = new QTreeWidgetItem();

    QIcon tIcon;
    foreach(QAction* act, _view->_actionList)
    {
        QString tStr = act->text();
        if(act->text()==ui->cbActionFromMenu_Toolbar->currentText())
        {
            tIcon = act->icon();
            break;
        }
    }
    tChildItem->setIcon(0, tIcon);
    tChildItem->setText(0, ui->cbActionFromMenu_Toolbar->currentText());
    tChildItem->setText(1, tr(CONST_STR_ITEMTYPE_ACTION));
    rootItem->addChild(tChildItem);
    tChildItem->setText(3, rootItem->text(3));
    tChildItem->setText(4, rootItem->text(4));

    rootItem->setExpanded(true);
}

void ViewEditor::on_btnAddSeparator_Toolbar_clicked()
{
    if(ui->treeToolbarEdit->topLevelItemCount()==0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is no toolbar node, Please add a bar first!"));
        return;
    }

    QTreeWidgetItem* tItem = ui->treeToolbarEdit->currentItem();
    if(tItem==nullptr)
    {
        QMessageBox::information(this, tr("Infomation"), tr("Please select the toolbar node!"));
        return;
    }

    //==========================================
    QTreeWidgetItem* rootItem;
    if(tItem->parent() == nullptr)
        rootItem = tItem;
    else
        rootItem = tItem->parent();

    QTreeWidgetItem* tChildItem = new QTreeWidgetItem();
    tChildItem->setText(0, tr(CONST_STR_SEPARATOR));
    tChildItem->setText(1, tr(CONST_STR_ITEMTYPE_SEPARATOR));
    rootItem->addChild(tChildItem);

    rootItem->setExpanded(true);
}

void ViewEditor::on_btnAddWidget_Toolbar_clicked()
{
    if(ui->treeToolbarEdit->topLevelItemCount()==0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is no toolbar node, Please add a bar first!"));
        return;
    }

    QTreeWidgetItem* tItem = ui->treeToolbarEdit->currentItem();
    if(tItem==nullptr)
    {
        QMessageBox::information(this, tr("Infomation"), tr("Please select the toolbar node!"));
        return;
    }

    PluginIO* plugInst = PluginIO::getInstance();
    PluginWidgetViewer* ce = new PluginWidgetViewer(plugInst->_core, false, this);

    ce->exec();

    if(ui->tableStatusbarEditer->findItems(ce->_itemTag, Qt::MatchFlag::MatchExactly).count()>0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is a same widget item in statusbar editor!"));
        return;
    }

    bool isExitInPluginWidgetTable = false;
    for(int i=0; i<ui->tablePluginWidget->rowCount(); i++)
    {
        QString tableTtemTag = getPluginWidgetTag(i);
        if(ce->_itemTag == tableTtemTag && ui->tablePluginWidget->item(i, 0)->checkState() == Qt::CheckState::Checked)
        {
            isExitInPluginWidgetTable = true;
            break;
        }
    }
    if(isExitInPluginWidgetTable)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is a same widget item be selected in workspace editor!"));
        return;
    }

    if(ui->treeToolbarEdit->findItems(ce->_itemTag, Qt::MatchFlag::MatchRecursive | Qt::MatchFlag::MatchExactly).count()>0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is a same widget item in toolbar editor!"));
        return;
    }

    //=============================================
    QTreeWidgetItem* rootItem;
    if(tItem->parent() == nullptr)
        rootItem = tItem;
    else
        rootItem = tItem->parent();

    if(ce->_isOk)
    {
        QTreeWidgetItem* tChildItem = new QTreeWidgetItem();
        tChildItem->setText(0, ce->_itemTag);
        tChildItem->setText(1, tr(CONST_STR_ITEMTYPE_WIDGET));
        tChildItem->setText(3, QString::number(ce->_widgetOrigWidth));
        tChildItem->setText(4, QString::number(ce->_widgetOrigHeight));
        rootItem->addChild(tChildItem);
    }

    rootItem->setExpanded(true);
}

void ViewEditor::on_btnDeleteItem_Toolbar_clicked()
{
    if(ui->treeToolbarEdit->topLevelItemCount()==0)
        return;

    QTreeWidgetItem* tItem =  ui->treeToolbarEdit->currentItem();
    if(tItem==nullptr)
        return;

    if(tItem->parent()==nullptr)
    {
        if(tItem->childCount() > 0)
        {
            QMessageBox::StandardButton tBtn = QMessageBox::question(this, tr("Infomation"), tr("Are you sure to delete the item and it's children?"));
            if(tBtn==QMessageBox::No)
                return;
            for(int i = 0; i < tItem->childCount(); i ++)
            {
                del(tItem->child(i));
            }
        }
        delete tItem;
    }
    else
    {
        del(tItem);
    }

}

void ViewEditor::TableItemMoveUp(QTableWidget *table)
{
    int currRowIndex = table->currentRow();
    if(currRowIndex==-1 || currRowIndex==0)
    {
        table->selectRow(0);
        table->setFocus();
        return;
    }

    QString  tItemUp;
    QString tItemCurrent;

    for(int i=1; i<table->columnCount(); i++)
    {
        tItemCurrent =table->item(currRowIndex, i)->text();
        tItemUp = table->item(currRowIndex-1, i)->text();

        table->setItem(currRowIndex, i, new QTableWidgetItem(tItemUp));
        table->setItem(currRowIndex-1, i, new QTableWidgetItem(tItemCurrent));
    }
    table->selectRow(currRowIndex-1);
    table->setFocus();
}

void ViewEditor::TableItemMoveDown(QTableWidget *table)
{
    int currRowIndex = table->currentRow();
    if(currRowIndex==-1 || currRowIndex==table->rowCount()-1)
    {
        table->selectRow(table->rowCount()-1);
        table->setFocus();
        return;
    }

    QString tItemCurrent;
    QString  tItemDown;

    for(int i=1; i<table->columnCount(); i++)
    {
        tItemCurrent = table->item(currRowIndex, i)->text();
        tItemDown = table->item(currRowIndex+1, i)->text();

        table->setItem(currRowIndex, i, new QTableWidgetItem(tItemDown));
        table->setItem(currRowIndex+1, i, new QTableWidgetItem(tItemCurrent));
    }
    table->selectRow(currRowIndex+1);
    table->setFocus();
}

void ViewEditor::TreeItemMoveUp(QTreeWidget* treeWidget)
{
    QTreeWidgetItem* curSelItem= treeWidget->currentItem();
    if(curSelItem==nullptr)
        return;

    if(curSelItem->parent()==nullptr)//toplevel
    {
        QTreeWidgetItem* topItem = curSelItem;

        int topIevelItemIndex = treeWidget->indexOfTopLevelItem(curSelItem);

        if(topIevelItemIndex==0)
            return;

        treeWidget->takeTopLevelItem(topIevelItemIndex);
        treeWidget->insertTopLevelItem(topIevelItemIndex-1, topItem);
        treeWidget->setCurrentItem(topItem);
    }
    else
    {
        QTreeWidgetItem* childItem = curSelItem;
        QTreeWidgetItem* parentNode = curSelItem->parent();

        int childItemIndex = parentNode->indexOfChild(childItem);

        if(childItemIndex==0)
            return;
        parentNode->takeChild(childItemIndex);
        parentNode->insertChild(childItemIndex-1, childItem);
        treeWidget->setCurrentItem(childItem);
    }
}

void ViewEditor::TreeItemMoveDown(QTreeWidget* treeWidget)
{
    QTreeWidgetItem* curSelItem= treeWidget->currentItem();
    if(curSelItem==nullptr)
        return;

    if(curSelItem->parent()==nullptr)//toplevel
    {
        QTreeWidgetItem* topItem = curSelItem;

        int topIevelItemIndex = treeWidget->indexOfTopLevelItem(curSelItem);

        if(topIevelItemIndex>=treeWidget->topLevelItemCount() -1)
            return;

        treeWidget->takeTopLevelItem(topIevelItemIndex);
        treeWidget->insertTopLevelItem(topIevelItemIndex + 1, topItem);
        treeWidget->setCurrentItem(topItem);
    }
    else
    {
        QTreeWidgetItem* childItem = curSelItem;
        QTreeWidgetItem* parentNode = curSelItem->parent();

        int childItemIndex = parentNode->indexOfChild(childItem);

        if(childItemIndex == parentNode->childCount()-1)
            return;

        parentNode->takeChild(childItemIndex);
        parentNode->insertChild(childItemIndex+1, childItem);
        treeWidget->setCurrentItem(childItem);
    }
}

void ViewEditor::TreeItemMoveLeft(QTreeWidget* treeWidget)
{
    QTreeWidgetItem* curSelItem= treeWidget->currentItem();
    if(curSelItem==nullptr)
        return;

    if(curSelItem->parent()==nullptr)//toplevel
    {
        return;
    }
    else
    {
        QTreeWidgetItem* copyItem = curSelItem;
        QTreeWidgetItem* parentNode = curSelItem->parent();
        QTreeWidgetItem* grandpaNode = parentNode->parent();

        parentNode->takeChild(parentNode->indexOfChild(curSelItem));
        if(grandpaNode==nullptr)
        {
            treeWidget->addTopLevelItem(copyItem);
            treeWidget->setCurrentItem(copyItem);
        }
        else
        {
            grandpaNode->addChild(copyItem);
            treeWidget->setCurrentItem(copyItem);
        }
    }
}

void ViewEditor::TreeItemMoveRight(QTreeWidget* treeWidget)
{
    QTreeWidgetItem* curSelItem= treeWidget->currentItem();
    if(curSelItem==nullptr)
        return;

    QTreeWidgetItem* copyItem = curSelItem;
    QTreeWidgetItem* parentNode = curSelItem->parent();

    if(parentNode==nullptr)
    {
        if(treeWidget->topLevelItemCount()==1)
            return;
        else
        {
            int topIevelItemIndex = treeWidget->indexOfTopLevelItem(curSelItem);
            if(topIevelItemIndex==0)
                return;
            else
            {
                treeWidget->takeTopLevelItem(topIevelItemIndex);
                treeWidget->topLevelItem(topIevelItemIndex-1)->addChild(copyItem);
                treeWidget->setCurrentItem(copyItem);
            }
        }
    }
    else
    {
        if(parentNode->childCount()==1)
            return;
        else
        {
            int itemIndex = parentNode->indexOfChild(curSelItem);
            if(itemIndex==0)
                return;
            else
            {
                QTreeWidgetItem* preParent = parentNode->child(itemIndex-1);

                if(preParent->text(5)!="")
                {
                    QMessageBox::information(this, tr("Infomation"), tr("Cannot be at the next level of another node that is associated with an Action!"));
                    return;
                }

                if(preParent->text(0).contains("----------"))
                {
                    QMessageBox::information(this, tr("Infomation"), tr("Cannot be at the next level of a Separator!"));
                    return;
                }

                parentNode->takeChild(itemIndex);
                parentNode->child(itemIndex-1)->addChild(copyItem);
                treeWidget->setCurrentItem(copyItem);
            }
        }
    }
}

void ViewEditor::on_btnMoveUp_Toolbar_clicked()
{
    TreeItemMoveUp(ui->treeToolbarEdit);
}

void ViewEditor::on_btnMoveDown_Toolbar_clicked()
{
    TreeItemMoveDown(ui->treeToolbarEdit);
}

void ViewEditor::on_btnAddWidget_Statusbar_clicked()
{
    PluginIO* plugInst = PluginIO::getInstance();
    PluginWidgetViewer* ce = new PluginWidgetViewer(plugInst->_core, true, this);
    ce->exec();

    if(ui->treeToolbarEdit->findItems(ce->_itemTag, Qt::MatchFlag::MatchRecursive | Qt::MatchFlag::MatchExactly).count()>0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is a same widget item in toolbar editor!"));
        return;
    }

    bool isExitInPluginWidgetTable = false;
    for(int i=0; i<ui->tablePluginWidget->rowCount(); i++)
    {
        QString tableTtemTag = getPluginWidgetTag(i);
        if(ce->_itemTag == tableTtemTag && ui->tablePluginWidget->item(i, 0)->checkState() == Qt::CheckState::Checked)
        {
            isExitInPluginWidgetTable = true;
            break;
        }
    }
    if(isExitInPluginWidgetTable)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is a same widget item be selected in workspace editor!"));
        return;
    }

    if(ui->tableStatusbarEditer->findItems(ce->_itemTag, Qt::MatchFlag::MatchExactly).count()>0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is a same widget item in statusbar editor!"));
        return;
    }

    if(ce->_isOk)
    {
        int tRowCount = ui->tableStatusbarEditer->rowCount();
        ui->tableStatusbarEditer->insertRow(tRowCount);

        ui->tableStatusbarEditer->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(tRowCount+1)));
        ui->tableStatusbarEditer->setItem(tRowCount, 1, new QTableWidgetItem(ce->_itemTag));

        if(ce->_statusbarItemType == StatusbarItemType::SBT_COMMON)
            ui->tableStatusbarEditer->setItem(tRowCount, 2, new QTableWidgetItem(tr(CONST_STR_STATUSITEM_COMMON)));
        else if(ce->_statusbarItemType == StatusbarItemType::SBT_PERMANENT)
            ui->tableStatusbarEditer->setItem(tRowCount, 2, new QTableWidgetItem(tr(CONST_STR_STATUSITEM_PERMANENT)));

        ui->tableStatusbarEditer->setItem(tRowCount, 3, new QTableWidgetItem(QString::number(ce->_widgetOrigWidth)));
        ui->tableStatusbarEditer->setItem(tRowCount, 4, new QTableWidgetItem(QString::number(ce->_widgetOrigHeight)));
    }
}

void ViewEditor::on_btnDeleteItem_Statusbar_clicked()
{
    int tRowIndex = ui->tableStatusbarEditer->currentRow();
    ui->tableStatusbarEditer->removeRow(tRowIndex);

    for(int i=tRowIndex; i<ui->tableStatusbarEditer->rowCount(); i++)
        ui->tableStatusbarEditer->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
}

void ViewEditor::on_btnMoveUp_Statusbar_clicked()
{
    TableItemMoveUp(ui->tableStatusbarEditer);
}

void ViewEditor::on_btnMoveDown_Statusbar_clicked()
{
    TableItemMoveDown(ui->tableStatusbarEditer);
}

void ViewEditor::on_btnAddToolbar_clicked()
{
    int tCurrTopNodeCount = ui->treeToolbarEdit->topLevelItemCount();
    QTreeWidgetItem* tTopNode = new QTreeWidgetItem();
    if(ui->txtBarTitle->text()=="")
        tTopNode->setText(0, QString(tr("Bar%1")).arg(tCurrTopNodeCount+1));
    else
        tTopNode->setText(0, ui->txtBarTitle->text());

    tTopNode->setText(2, ui->cbToolStritItemTextAlignment->currentText());
    tTopNode->setText(3, QString::number(ui->spanIconWidth_Toolbar->value()));
    tTopNode->setText(4, QString::number(ui->spanIconHeight_Toolbar->value()));

    ui->treeToolbarEdit->addTopLevelItem(tTopNode);
}

void ViewEditor::on_btnDeleteToolbar_clicked()
{
    QTreeWidgetItem* item =  ui->treeToolbarEdit->currentItem();
    if(item->parent()==nullptr)
    {
        if(item->childCount() > 0)
        {
            QMessageBox::StandardButton tBtn = QMessageBox::question(this, tr("Infomation"), tr("Are you sure to delete the item and it's children?"));
            if(tBtn==QMessageBox::No)
                return;
            for(int i = 0; i < item->childCount(); i ++)
            {
                del(item->child(i));
            }
        }
        delete item;
    }

    for(int i=0; i<ui->treeToolbarEdit->topLevelItemCount(); i++)
    {
        ui->treeToolbarEdit->topLevelItem(i)->setText(0, tr("Bar") + (i+1));
    }
}

ViewEditor *ViewEditor::getInstance()
{
    return pViewEdInstance;
}

void ViewEditor::slot_SelAllOrNot(bool flag)
{
    int row=0,col=0;
    int i=0,j=0;

    foreach(Plugin_Interface* pi, ((QCPF_Interface*)_view->_core)->I_SysPlugins)
    {
        foreach (PluginWidgetInfo* pwi, pi->I_WidgetList) {
            row+=1;
        }
    }

    foreach(Plugin_Interface* pi, ((QCPF_Interface*)_view->_core)->I_NSysAllValidPlugins)
    {
        foreach (PluginWidgetInfo* pwi, pi->I_WidgetList) {
            row+=1;
        }
    }

    if(flag == true)
    {
        for(;i<row;i++)
            ui->tablePluginWidget->item(i, 0)->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        for(;i<row;i++)
            ui->tablePluginWidget->item(i, 0)->setCheckState(Qt::CheckState::Unchecked);
    }
}

void ViewEditor::on_tablePluginWidget_itemClicked(QTableWidgetItem *item)
{
    if(item->column()!=0)
        return;

    if(item->checkState()==Qt::CheckState::Checked)
    {
        int rowIndex = item->row();
        QString itemTag =getPluginWidgetTag(rowIndex);
        if(ui->tableStatusbarEditer->findItems(itemTag, Qt::MatchFlag::MatchExactly).count()>0)
        {
            QMessageBox::information(this, tr("Infomation"), tr("There is a same widget item in statusbar editor!"));
            item->setCheckState(Qt::CheckState::Unchecked);
            return;
        }

        if(ui->treeToolbarEdit->findItems(itemTag, Qt::MatchFlag::MatchRecursive | Qt::MatchFlag::MatchExactly).count()>0)
        {
            QMessageBox::information(this, tr("Infomation"), tr("There is a same widget item in toolbar editor!"));
            item->setCheckState(Qt::CheckState::Unchecked);
            return;
        }
    }

}

QString ViewEditor::getPluginWidgetTag(int rowIndex)
{
    return QString(tr("%1;%2;%3;%4")).arg(ui->tablePluginWidget->item(rowIndex, 2)->text()).arg(ui->tablePluginWidget->item(rowIndex, 3)->text()).arg(ui->tablePluginWidget->item(rowIndex, 4)->text()).arg(ui->tablePluginWidget->item(rowIndex, 5)->text());
}

void ViewEditor::on_btnAddSpacer_Toolbar_clicked()
{
    if(ui->treeToolbarEdit->topLevelItemCount()==0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is no toolbar node, Please add a bar first!"));
        return;
    }

    QTreeWidgetItem* tItem = ui->treeToolbarEdit->currentItem();
    if(tItem==nullptr)
    {
        QMessageBox::information(this, tr("Infomation"), tr("Please select the toolbar node!"));
        return;
    }

    //=============================================
    QTreeWidgetItem* rootItem;
    if(tItem->parent() == nullptr)
        rootItem = tItem;
    else
        rootItem = tItem->parent();

    QTreeWidgetItem* tChildItem = new QTreeWidgetItem();
    tChildItem->setText(0, tr(CONST_STR_SPACER));
    tChildItem->setText(1, tr(CONST_STR_ITEMTYPE_SPACER));
    rootItem->addChild(tChildItem);

    rootItem->setExpanded(true);
}


void ViewEditor::on_treeMenuEdit_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    _currentTree = nullptr;
    _currentItem_TreeMenuEdit = nullptr;
    _currentCol_TreeMenuEdit = 0;

    if(item->text(0)==CONST_STR_SEPARATOR)
        return;

    _currentTree = ui->treeMenuEdit;
    _currentItem_TreeMenuEdit = item;
    _currentCol_TreeMenuEdit = column;
    if(column==0)
    {
        QLineEdit* lineEdit = new QLineEdit(this);
        lineEdit->setText(item->text(column));
        connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(OnLineEdit_EditingFinished_Tree()));
        ui->treeMenuEdit->setItemWidget(item, column, lineEdit);
    }
    else if(column==1)
    {
        QKeySequenceEdit* keyEdit = new QKeySequenceEdit(this);
        connect(keyEdit, SIGNAL(editingFinished()), this, SLOT(OnKeyEdit_EditingFinished_Tree()));
        ui->treeMenuEdit->setItemWidget(item, column, keyEdit);
    }
    else if(column==2)
    {
        on_btnIconFinder_clicked();
    }
    else if(column==3)
    {
        QComboBox* cbBox = new QComboBox(this);

        for(int i=0; i<ui->cbMenuAuthority->count(); i++)
            cbBox->insertItem(i, ui->cbMenuAuthority->itemText(i));

        cbBox->setCurrentText(item->text(column));
        connect(cbBox, SIGNAL(activated(int)), this, SLOT(OnComboBox_Activated_Index_Tree(int)));
        ui->treeMenuEdit->setItemWidget(item, column, cbBox);
    }
    else if(column==4)
    {
        QComboBox* cbBox = new QComboBox(this);

        cbBox->insertItem(0, tr("True"));
        cbBox->insertItem(1, tr("False"));

        cbBox->setCurrentText(item->text(column));
        connect(cbBox, SIGNAL(activated(int)), this, SLOT(OnComboBox_Activated_Text_Tree(int)));
        ui->treeMenuEdit->setItemWidget(item, column, cbBox);
    }
    else if(column>4)
    {
        on_btnClearAction_clicked();
        on_btnLoadAction_clicked();
    }
}

void ViewEditor::on_treeToolbarEdit_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    _currentTree = nullptr;
    _currentItem_TreeMenuEdit = nullptr;
    _currentCol_TreeMenuEdit = 0;


    if(item->parent()==nullptr)
    {
        _currentTree = ui->treeToolbarEdit;
        _currentItem_TreeMenuEdit = item;
        _currentCol_TreeMenuEdit = column;
        if(column==0)
        {
            QLineEdit* lineEdit = new QLineEdit(this);
            lineEdit->setText(item->text(column));
            connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(OnLineEdit_EditingFinished_Tree()));
            ui->treeToolbarEdit->setItemWidget(item, column, lineEdit);
        }
        else if(column==2)
        {
            QComboBox* cbBox = new QComboBox(this);

            for(int i=0; i<ui->cbToolStritItemTextAlignment->count(); i++)
                cbBox->insertItem(i, ui->cbToolStritItemTextAlignment->itemText(i));

            cbBox->setCurrentText(item->text(column));
            connect(cbBox, SIGNAL(activated(int)), this, SLOT(OnComboBox_Activated_Text_Tree(int)));
            ui->treeToolbarEdit->setItemWidget(item, column, cbBox);
        }
        else if(column==3 || column==4)
        {
            QLineEdit* lineEdit = new QLineEdit(this);
            lineEdit->setText(item->text(column));
            connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(OnLineEdit_EditingFinished_Tree()));
            ui->treeToolbarEdit->setItemWidget(item, column, lineEdit);
        }
    }
}


void ViewEditor::OnLineEdit_EditingFinished_Tree(void)
{
    if(_currentItem_TreeMenuEdit!=nullptr && _currentTree!=nullptr)
    {
        QLineEdit *edit = qobject_cast<QLineEdit*>(_currentTree->itemWidget(_currentItem_TreeMenuEdit, _currentCol_TreeMenuEdit));
                if (!edit) {
                    return;
                }
                QString text = edit->text();
                _currentTree->removeItemWidget(_currentItem_TreeMenuEdit, _currentCol_TreeMenuEdit);
                _currentItem_TreeMenuEdit->setText(_currentCol_TreeMenuEdit, text);
    }
}

void ViewEditor::OnKeyEdit_EditingFinished_Tree(void)
{
    if(_currentItem_TreeMenuEdit!=nullptr && _currentTree!=nullptr)
    {
        QKeySequenceEdit *keyEdit = qobject_cast<QKeySequenceEdit*>(_currentTree->itemWidget(_currentItem_TreeMenuEdit, _currentCol_TreeMenuEdit));
                if (!keyEdit) {
                    return;
                }
                QString text = keyEdit->keySequence().toString();
                _currentTree->removeItemWidget(_currentItem_TreeMenuEdit, _currentCol_TreeMenuEdit);
                _currentItem_TreeMenuEdit->setText(_currentCol_TreeMenuEdit, text);
    }
}

void ViewEditor::OnComboBox_Activated_Index_Tree(int)
{
    if(_currentItem_TreeMenuEdit!=nullptr && _currentTree!=nullptr)
    {
        QComboBox *cbox = qobject_cast<QComboBox*>(_currentTree->itemWidget(_currentItem_TreeMenuEdit, _currentCol_TreeMenuEdit));
                if (!cbox) {
                    return;
                }

                QString text = QString::number(cbox->currentIndex());
                _currentTree->removeItemWidget(_currentItem_TreeMenuEdit, _currentCol_TreeMenuEdit);
                _currentItem_TreeMenuEdit->setText(_currentCol_TreeMenuEdit, text);
    }
}

void ViewEditor::OnComboBox_Activated_Text_Tree(int)
{
    if(_currentItem_TreeMenuEdit!=nullptr && _currentTree!=nullptr)
    {
        QComboBox *cbox = qobject_cast<QComboBox*>(_currentTree->itemWidget(_currentItem_TreeMenuEdit, _currentCol_TreeMenuEdit));
                if (!cbox) {
                    return;
                }

                QString text = cbox->currentText();
                _currentTree->removeItemWidget(_currentItem_TreeMenuEdit, _currentCol_TreeMenuEdit);
                _currentItem_TreeMenuEdit->setText(_currentCol_TreeMenuEdit, text);
    }
}

void ViewEditor::OnSpinBox_ValueChanged_Tree(int)
{
    if(_currentItem_TreeMenuEdit!=nullptr && _currentTree!=nullptr)
    {
        QSpinBox *spinBox = qobject_cast<QSpinBox*>(_currentTree->itemWidget(_currentItem_TreeMenuEdit, _currentCol_TreeMenuEdit));
                if (!spinBox) {
                    return;
                }

                QString text = QString::number(spinBox->value());
                _currentTree->removeItemWidget(_currentItem_TreeMenuEdit, _currentCol_TreeMenuEdit);
                _currentItem_TreeMenuEdit->setText(_currentCol_TreeMenuEdit, text);
    }
}

void ViewEditor::OnComboBox_Activated_Text_Table(int)
{
    if(_currentItem_tableStatusbarEditer!=nullptr && _currentTable!=nullptr)
    {
        QComboBox *cbox = qobject_cast<QComboBox*>(_currentTable->cellWidget(_currentItem_tableStatusbarEditer->row(), _currentItem_tableStatusbarEditer->column()));
                if (!cbox) {
                    return;
                }

                QString text = cbox->currentText();
                _currentTable->removeCellWidget(_currentItem_tableStatusbarEditer->row(), _currentItem_tableStatusbarEditer->column());
                _currentItem_tableStatusbarEditer->setText(text);
    }
}

void ViewEditor::on_tableStatusbarEditer_itemDoubleClicked(QTableWidgetItem *item)
{
    _currentTable = nullptr;
    _currentItem_tableStatusbarEditer = nullptr;

    if(item->column() == 2)
    {
        _currentTable = ui->tableStatusbarEditer;
        _currentItem_tableStatusbarEditer = item;

        QComboBox* cbBox = new QComboBox(this);

        cbBox->insertItem(0, tr(CONST_STR_STATUSITEM_COMMON));
        cbBox->insertItem(1, tr(CONST_STR_STATUSITEM_PERMANENT));

        cbBox->setCurrentText(item->text());
        connect(cbBox, SIGNAL(activated(int)), this, SLOT(OnComboBox_Activated_Text_Table(int)));
        ui->tableStatusbarEditer->setCellWidget(item->row(), item->column(), cbBox);
    }
}

void ViewEditor::on_btnIconClear_clicked()
{
    if(ui->treeMenuEdit->currentItem()==nullptr)
        return;

    if(ui->treeMenuEdit->currentItem()->text(0)== CONST_STR_SEPARATOR)
        return;

    ui->treeMenuEdit->currentItem()->setIcon(0, QIcon());
    ui->treeMenuEdit->currentItem()->setText(2, "");

    QString actionName = ui->treeMenuEdit->currentItem()->text(8);
    int tCbIndex = ui->cbActionFromMenu_Toolbar->findText(actionName, Qt::MatchFlag::MatchExactly);
    ui->cbActionFromMenu_Toolbar->setItemIcon(tCbIndex, QIcon());

    QList<QTreeWidgetItem*> destItemsLst = ui->treeToolbarEdit->findItems(actionName, Qt::MatchFlag::MatchRecursive | Qt::MatchFlag::MatchExactly);
    foreach (QTreeWidgetItem* qwi, destItemsLst) {
        qwi->setIcon(0, QIcon());
    }
}
