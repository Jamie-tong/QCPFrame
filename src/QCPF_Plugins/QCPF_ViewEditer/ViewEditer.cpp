/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "ViewEditer.h"
#include "ui_ViewEditer.h"

#include "../../../interface/plugininterface.h"
#include <QTimer>
#include <QStringLiteral>
#include <QMessageBox>
#include "PluginActionViewer.h"
#include "PluginWidgetViewer.h"
#include <QFileDialog>
#include "utility/ccheckboxheaderview.h"

ViewEditer* instance;

ViewEditer::ViewEditer(QCPF_ViewModel* view, QWidget *parent) :
    QDialog(parent),ui(new Ui::ViewEditer)
{
    ui->setupUi(this);

    _view = view;
    this->setParent(parent);

    instance = this;
    connect(this,SIGNAL(sig_SelAllOrNot(bool)),this,SLOT(slot_SelAllOrNot(bool)));//for 全选/不选复选框

    //去掉问号按钮
    setWindowFlags(Qt::Dialog
                   | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    //禁止调整大小
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(1207, 780));
    setMaximumSize(QSize(1207, 780));
    setSizeGripEnabled(false);

    connect(ui->treeMenuEdit,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(treeWidgetOpenEditor(QTreeWidgetItem*,int)));
    connect(ui->treeMenuEdit,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeWidgetCloseEditor()));

    //注册面板显示后的信号槽
    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnULoaded()));
}

ViewEditer::~ViewEditer()
{

}

void ViewEditer::resizeEvent(QResizeEvent *event)
{
    //如果不是第一次显示
    if(!_isFirstResize)
        return;
    else
        _isFirstResize = false;
}

void ViewEditer::showEvent(QShowEvent *event)
{
    _timer->start(1);
}

void ViewEditer::slot_OnULoaded()
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
    configParentNode->_menuIsSeprator = treeTopNode->text(0).contains("----------")?true:false;
    configParentNode->_menuShortCut = treeTopNode->text(1);
    configParentNode->_menuIconPath = treeTopNode->text(2);
    configParentNode->_menuAuthority = treeTopNode->text(3).toInt();
    configParentNode->_menuCheckable = treeTopNode->text(4)=="True"?true:false;

    QString tt = treeTopNode->text(5);
    configParentNode->_pluginType = treeTopNode->text(5)=="System"?0:1;
    configParentNode->_pluginID = treeTopNode->text(6);
    configParentNode->_copyID = treeTopNode->text(7);
    configParentNode->_functionName = treeTopNode->text(8);
    configParentNode->_functionDetail = treeTopNode->text(9);

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

 int ViewEditer::getConfigFromUI()
 {
    _view->_config._menuTopItemLst.clear();
    _view->_config._isEnable_ShowMenu = ui->chb_IsShowMenu->isChecked();
    _view->_config._isEnable_ShowToolbar = ui->chb_IsShowToolBar->isChecked();
    _view->_config._isEnable_ShowStatusbar = ui->chb_IsShowStatusBar->isChecked();

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
        tToolbar->_count_ToolBarItemLst = ui->treeToolbarEdit->topLevelItem(i)->childCount();
        tToolbar->_toolBarItemList.clear();
        for(int j=0; j<tToolbar->_count_ToolBarItemLst; j++)
        {
            BarItem* tItem = new BarItem();
            tToolbar->_toolBarItemList.append(tItem);

            //_type---------------0:Seperator; 1:Widget; 2:Action
            QString tTypeStr = ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(1);
            if(tTypeStr.compare("Seperator")==0)
                tItem->_type = TP_SEPERATOR;
            else if(tTypeStr.compare("Widget")==0)
                tItem->_type = TP_WIDGET;
            else if(tTypeStr.compare("Action")==0)
                tItem->_type = TP_ACTION;

            if(tItem->_type==TP_WIDGET)//Widget
            {
                WidgetItem* tWidgetItem = new WidgetItem();
                tItem->_widgetItem = tWidgetItem;

                QStringList splitStrLst =  ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(0).split(";");
                if(splitStrLst.count()!=4)
                    return -1;

                tWidgetItem->_widgetObjectName = splitStrLst[0];
                if(splitStrLst[1] == tr("System"))
                    tWidgetItem->_pluginType = 0;
                else if(splitStrLst[1] == tr("NonSystem"))
                    tWidgetItem->_pluginType = 1;

                tWidgetItem->_pluginID = splitStrLst[2];
                tWidgetItem->_copyID = splitStrLst[3];


                tWidgetItem->_widgetOrigWidth = ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(2).toInt();
                tWidgetItem->_widgetOrigHeight = ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(3).toInt();

                tItem->_width = tWidgetItem->_widgetOrigWidth;
                tItem->_height = tWidgetItem->_widgetOrigHeight;
            }
            else if(tItem->_type==TP_ACTION)//Action
            {
                ActionItem* tActionItem = new ActionItem();
                tItem->_actionItem = tActionItem;

                tActionItem->_actionObjectName = ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(0);

                tItem->_width = ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(2).toInt();
                tItem->_height = ui->treeToolbarEdit->topLevelItem(i)->child(j)->text(3).toInt();
            }
        }
    }

    _view->_config._count_StatusBarItemLst = ui->tableStatusbarEditer->rowCount();
    _view->_config._statusBarItemLst.clear();
    for(int i=0; i<_view->_config._count_StatusBarItemLst; i++)
    {
        WidgetItem* tWidgetItem = new WidgetItem();
        _view->_config._statusBarItemLst.append(tWidgetItem);

        QStringList splitStrLst =  ui->tableStatusbarEditer->item(i, 1)->text().split(tr(";"));
        if(splitStrLst.count()!=4)
            return -1;

        tWidgetItem->_widgetObjectName = splitStrLst[0];
        if(splitStrLst[1] == "System")
            tWidgetItem->_pluginType = PT_SYS;
        else if(splitStrLst[1] == "NonSystem")
            tWidgetItem->_pluginType = PT_NON_SYS;

        tWidgetItem->_pluginID = splitStrLst[2];
        tWidgetItem->_copyID = splitStrLst[3];


        tWidgetItem->_widgetOrigWidth = ui->tableStatusbarEditer->item(i, 2)->text().toInt();
        tWidgetItem->_widgetOrigHeight = ui->tableStatusbarEditer->item(i, 3)->text().toInt();
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

        if(ui->tablePluginWidget->item(i, 2)->text()=="System")
            tWidgetItem->_pluginType = PT_SYS;
        else if(ui->tablePluginWidget->item(i, 2)->text()=="NonSystem")
            tWidgetItem->_pluginType = PT_NON_SYS;

        tWidgetItem->_pluginID = ui->tablePluginWidget->item(i, 3)->text();
        tWidgetItem->_copyID = ui->tablePluginWidget->item(i, 5)->text();
        tWidgetItem->_widgetObjectName = ui->tablePluginWidget->item(i, 6)->text();
    }
     return 0;
 }

 void parseNodeToTree(JMenuNode* configNode, QTreeWidgetItem* treeNode, QComboBox* cbToolbarAction)
 {
    if(configNode->_children.count()==0)
    {
        QTreeWidgetItem* treeChildNode = new QTreeWidgetItem();

        treeChildNode->setText(0, configNode->_menuTitle);
        treeChildNode->setIcon(0, QIcon(configNode->_menuIconPath));
        treeChildNode->setText(1, configNode->_menuShortCut);
        treeChildNode->setText(2, configNode->_menuIconPath);
        treeChildNode->setText(3, QString::number(configNode->_menuAuthority));
        treeChildNode->setText(4, configNode->_menuCheckable?QStringLiteral("True"):QStringLiteral("False"));

        if(!configNode->_menuTitle.contains("----------"))
            treeChildNode->setText(5, configNode->_pluginType?QStringLiteral("Non-System"):QStringLiteral("System"));
        treeChildNode->setText(6, configNode->_pluginID);
        treeChildNode->setText(7, configNode->_copyID);
        treeChildNode->setText(8, configNode->_functionName);
        treeChildNode->setText(9, configNode->_functionDetail);
        treeNode->addChild(treeChildNode);

        if(configNode->_functionName!="" && cbToolbarAction->findText(configNode->_functionName)<0)
            cbToolbarAction->addItem(configNode->_functionName);
    }
    else
    {
        QString tStr = configNode->_parentMenuTitle;
        if(configNode->_parentMenuTitle =="")//说明是一级菜单
        {
            for(int i=0; i<configNode->_children.count(); i++)
            {
                parseNodeToTree(configNode->_children[i], treeNode, cbToolbarAction);
            }
        }
        else
        {
            QTreeWidgetItem* treeHasChildNode = new QTreeWidgetItem();

            treeHasChildNode->setText(0, configNode->_menuTitle);
            treeNode->addChild(treeHasChildNode);

            for(int i=0; i<configNode->_children.count(); i++)
            {
                parseNodeToTree(configNode->_children[i], treeHasChildNode, cbToolbarAction);
            }
        }
    }
 }

 int ViewEditer::setConfigToUI()
 {
     ui->tabWidget->setCurrentIndex(0);
     ui->chb_IsShowMenu->setChecked(_view->_config._isEnable_ShowMenu);
     ui->chb_IsShowToolBar->setChecked(_view->_config._isEnable_ShowToolbar);
     ui->chb_IsShowStatusBar->setChecked(_view->_config._isEnable_ShowStatusbar);

     //--------------------------
     //设置菜单编辑器树样式
     //--------------------------
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
     //设置控件样式
     ui->treeMenuEdit->header()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
     ui->treeMenuEdit->header()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter); //居中
     ui->treeMenuEdit->header()->setStretchLastSection(true);
     ui->treeMenuEdit->setStyleSheet( "QTreeView::item:hover{background-color:rgb(110,178,233); color:white}"
     "QTreeView::item:selected{background-color:rgb(0,120,215)}"
     "QTreeView::item:selected{color: white}"
     "QTreeWidget::item{border-right: 1px solid silver; font:9pt '微软雅黑';}"
      );
     //为菜单树加载数据
    ui->treeMenuEdit->clear();

    for(int i=0; i<_view->_config._menuTopItemLst.count(); i++)
    {
        JMenuNode* tTopConfigNode = _view->_config._menuTopItemLst[i];
        QTreeWidgetItem* tTopTreeItem = new QTreeWidgetItem();

        tTopTreeItem->setText(0, tTopConfigNode->_menuTitle);
        tTopTreeItem->setText(1, tTopConfigNode->_menuShortCut);
        tTopTreeItem->setText(2, tTopConfigNode->_menuIconPath);
        tTopTreeItem->setText(3, QString::number(tTopConfigNode->_menuAuthority));
        tTopTreeItem->setText(4, tTopConfigNode->_menuCheckable?QStringLiteral("True"):QStringLiteral("False"));
        //一级菜单不能为有Action
        //一级菜单不挂接插件，因为没有组件类型
        ui->treeMenuEdit->addTopLevelItem(tTopTreeItem);

        //递归遍历树
        parseNodeToTree(tTopConfigNode, tTopTreeItem, ui->cbActionFromMenu_Toolbar);
    }
    ui->treeMenuEdit->expandAll();
    //--------------------------
    //设置工具栏编辑器样式
    //--------------------------
    ui->treeToolbarEdit->setColumnCount(4);

    nHeadLst.clear();
    nHeadLst<<tr("Item")<<tr("Type")<<tr("Width")<<tr("Height");
    ui->treeToolbarEdit->setHeaderLabels(nHeadLst);
    ui->treeToolbarEdit->header()->setVisible(true);

    ui->treeToolbarEdit->setColumnWidth(0, 210);
    ui->treeToolbarEdit->setColumnWidth(1, 80);
    ui->treeToolbarEdit->setColumnWidth(2, 50);
    ui->treeToolbarEdit->setColumnWidth(3, 50);

    //设置控件样式
    ui->treeToolbarEdit->header()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
    ui->treeToolbarEdit->header()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter); //居中
    ui->treeToolbarEdit->header()->setStretchLastSection(true);
    ui->treeToolbarEdit->setStyleSheet( "QTreeView::item:hover{background-color:rgb(110,178,233); color:white}"
    "QTreeView::item:selected{background-color:rgb(0,120,215)}"
    "QTreeView::item:selected{color: white}"
    "QTreeWidget::item{border-right: 1px solid silver; font:9pt '微软雅黑';}"
     );

    //为工具栏加载数据
    ui->treeToolbarEdit->clear();

    foreach (JToolBar* bar, _view->_config._toolBarLst) {
        QTreeWidgetItem* tTopTreeNode = new QTreeWidgetItem();
        tTopTreeNode->setText(0, QString(tr("Bar%1")).arg(bar->_toolBarNo + 1));
        ui->treeToolbarEdit->addTopLevelItem(tTopTreeNode);

        foreach (BarItem* item, bar->_toolBarItemList) {
            QTreeWidgetItem* tItemTreeNode = new QTreeWidgetItem();
            tTopTreeNode->addChild(tItemTreeNode);

            if(item->_type == TP_SEPERATOR)//Seperator
            {
                tItemTreeNode->setText(0, tr("--------------------"));
                tItemTreeNode->setText(1, tr("Seperator"));
            }
            else if(item->_type == TP_WIDGET)//Widget
            {
                QString pluginType = item->_widgetItem->_pluginType==PT_SYS?tr("System"):tr("NonSystem");
                QString _itemTag = item->_widgetItem->_widgetObjectName + ";" +  pluginType + ";" + item->_widgetItem->_pluginID + ";" + item->_widgetItem->_copyID;
                tItemTreeNode->setText(0,_itemTag);
                tItemTreeNode->setText(1, tr("Widget"));
                tItemTreeNode->setText(2, QString::number(item->_widgetItem->_widgetOrigWidth));
                tItemTreeNode->setText(3, QString::number(item->_widgetItem->_widgetOrigHeight));
            }
            else if(item->_type == TP_ACTION)//Action
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
                tItemTreeNode->setText(1, tr("Action"));
                tItemTreeNode->setText(2, QString::number(item->_width));
                tItemTreeNode->setText(3, QString::number(item->_height));
            }
        }
    }
    ui->treeToolbarEdit->expandAll();
    //--------------------------
    //设置状态栏编辑器样式
    //--------------------------
    ui->tableStatusbarEditer->setColumnCount(4);
    ui->tableStatusbarEditer->setRowCount(0);

    //为状态栏加载数据
    ui->tableStatusbarEditer->clear();

    nHeadLst.clear();
    nHeadLst<<tr("No.")<<tr("Item")<<tr("Width")<<tr("Height");

    ui->tableStatusbarEditer->setHorizontalHeaderLabels(nHeadLst);

    ui->tableStatusbarEditer->setColumnWidth(0, 40);
    ui->tableStatusbarEditer->setColumnWidth(1, 230);
    ui->tableStatusbarEditer->setColumnWidth(2, 50);
    ui->tableStatusbarEditer->setColumnWidth(3, 50);

    setTableStyle(ui->tableStatusbarEditer);

    int count = 0;
    foreach (WidgetItem* item, _view->_config._statusBarItemLst) {
        int tRowCount = ui->tableStatusbarEditer->rowCount();
        ui->tableStatusbarEditer->insertRow(tRowCount);

        ui->tableStatusbarEditer->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(++count)));

        QString pluginType = item->_pluginType==PT_SYS?tr("System"):tr("NonSystem");
        QString _itemTag = item->_widgetObjectName + ";" +  pluginType + ";" + item->_pluginID + ";" + item->_copyID;
        ui->tableStatusbarEditer->setItem(tRowCount, 1, new QTableWidgetItem(_itemTag));
        ui->tableStatusbarEditer->setItem(tRowCount, 2, new QTableWidgetItem(QString::number(item->_widgetOrigWidth)));
        ui->tableStatusbarEditer->setItem(tRowCount, 3, new QTableWidgetItem(QString::number(item->_widgetOrigHeight)));
    }

    //--------------------------
    //设置组件widget选择表格样式
    //--------------------------
    ui->tablePluginWidget->setColumnCount(8);
    ui->tablePluginWidget->setRowCount(0);

    //为组件widget表格加载数据
    ui->tablePluginWidget->clear();

    nHeadLst.clear();
    nHeadLst<<""<<tr("No.")<<tr("Plugin Type")<<tr("Plugin ID")<<tr("Is a Copy")<<tr("Copy ID")<<tr("Widget")<<tr("Widget Detail");

    CCheckBoxHeaderView *myHeader = new CCheckBoxHeaderView(0, Qt::Horizontal, ui->tablePluginWidget);
    ui->tablePluginWidget->setHorizontalHeader(myHeader);

    ui->tablePluginWidget->setHorizontalHeaderLabels(nHeadLst);

    ui->tablePluginWidget->setColumnWidth(0, 20);
    ui->tablePluginWidget->setColumnWidth(1, 100);
    ui->tablePluginWidget->setColumnWidth(2, 150);
    ui->tablePluginWidget->setColumnWidth(3, 150);
    ui->tablePluginWidget->setColumnWidth(4, 80);
    ui->tablePluginWidget->setColumnWidth(5, 150);
    ui->tablePluginWidget->setColumnWidth(6, 150);
    ui->tablePluginWidget->setColumnWidth(7, 200);

    setTableStyle(ui->tablePluginWidget);

    count = 0;
    //把每个系统组件的widget信息都加载到table中
    foreach (PluginInterface* pi, ((QCPF_Interface*)_view->_core)->I_SysPlugins) {
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
            //如果配置中的widget项，可以在组件中找到，则按配置中是否显示，来决定复选框的状态
            if(isExist)
                ui->tablePluginWidget->item(tRowCount, 0)->setCheckState(isChecked?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
            else //如果配置中的widget项，在组件中找不到，那有可能有新的组件被放进来，那么直接把新组件的widget信息加载进来
                ui->tablePluginWidget->item(tRowCount, 0)->setCheckState(Qt::CheckState::Unchecked);

            ui->tablePluginWidget->setItem(tRowCount, 1, new QTableWidgetItem(QString::number(++count)));
            ui->tablePluginWidget->setItem(tRowCount, 2, new QTableWidgetItem(tr("System")));
            ui->tablePluginWidget->setItem(tRowCount, 3, new QTableWidgetItem(pi->I_PluginID));
            ui->tablePluginWidget->setItem(tRowCount, 4, new QTableWidgetItem(tr("No")));
            ui->tablePluginWidget->setItem(tRowCount, 5, new QTableWidgetItem(pi->I_CopyID));
            ui->tablePluginWidget->setItem(tRowCount, 6, new QTableWidgetItem(pwi->_widget->objectName()));
            ui->tablePluginWidget->setItem(tRowCount, 7, new QTableWidgetItem(pwi->_widgetDetail));
        }
    }

    QList<PluginInterface*> tvec = ((QCPF_Interface*)_view->_core)->I_NSysAllValidPlugins;
    //把每个非系统组件的widget信息都加载到table中
    foreach (PluginInterface* pi, ((QCPF_Interface*)_view->_core)->I_NSysAllValidPlugins) {
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
            //如果配置中的widget项，可以在组件中找到，则按配置中是否显示，来决定复选框的状态
            if(isExist)
                ui->tablePluginWidget->item(tRowCount, 0)->setCheckState(isChecked?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
            else //如果配置中的widget项，在组件中找不到，那有可能有新的组件被放进来，那么直接把新组件的widget信息加载进来
                ui->tablePluginWidget->item(tRowCount, 0)->setCheckState(Qt::CheckState::Unchecked);

            ui->tablePluginWidget->setItem(tRowCount, 1, new QTableWidgetItem(QString::number(++count)));
            ui->tablePluginWidget->setItem(tRowCount, 2, new QTableWidgetItem(tr("NonSystem")));
            ui->tablePluginWidget->setItem(tRowCount, 3, new QTableWidgetItem(pi->I_PluginID));
            ui->tablePluginWidget->setItem(tRowCount, 4, new QTableWidgetItem(pi->I_CopyID==""?tr("No"):tr("Yes")));
            ui->tablePluginWidget->setItem(tRowCount, 5, new QTableWidgetItem(pi->I_CopyID));
            ui->tablePluginWidget->setItem(tRowCount, 6, new QTableWidgetItem(pwi->_widget->objectName()));
            ui->tablePluginWidget->setItem(tRowCount, 7, new QTableWidgetItem(pwi->_widgetDetail));
        }
    }
     return 0;
 }

 void ViewEditer::setTableStyle(QTableWidget *table)
 {
     //设置表头颜色
     table->horizontalHeader()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
     table->horizontalHeader()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter); //居左
    //设置相邻行颜色交替显示
     table->setAlternatingRowColors(true);
     //垂直表头不显示
     table->verticalHeader()->setVisible(false);
     //水平表头显示
     table->horizontalHeader()->setVisible(true);

     table->horizontalHeader()->setStretchLastSection(true);

     table->horizontalHeader()->setHighlightSections(false);//取消表头的在选中单元格时的高亮状态。
     table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设为不可编辑
     table->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
     table->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
     table->horizontalHeader()->setStretchLastSection(true);//最后一列自动调整列宽
     table->setStyleSheet("font:9pt '微软雅黑';");

     table->setSortingEnabled(false);
 }
 void ViewEditer::treeWidgetOpenEditor(QTreeWidgetItem *item, int col)
 {
     if(col>1)
         return;

     if(item->text(0).contains("----------"))
         return;

     previousColNo = col;
     ui->treeMenuEdit->openPersistentEditor(item,col);
 }

 void ViewEditer::on_treeMenuEdit_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
 {
     if(previous!=nullptr){
        ui->treeMenuEdit->closePersistentEditor(previous,previousColNo);
        //设置控件样式
        ui->treeMenuEdit->header()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
        ui->treeMenuEdit->header()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter); //居中
        ui->treeMenuEdit->header()->setStretchLastSection(true);
        ui->treeMenuEdit->setStyleSheet( "QTreeView::item:hover{background-color:rgb(110,178,233); color:white}"
        "QTreeView::item:selected{background-color:rgb(0,120,215)}"
        "QTreeView::item:selected{color: white}"
        "QTreeWidget::item{border-right: 1px solid silver; font:9pt '微软雅黑';}"
         );
     }
 }

void ViewEditer::on_btnOk_clicked()
{
    //====================================================================
    //保存配置(发送保存信号, 让_core自己进行存储自己的config信息)
    //====================================================================
    getConfigFromUI();

    _view->slot_SaveConfigFile();
    this->close();
}

void ViewEditer::on_btnCancel_clicked()
{
    _view->slot_CancelConfig();
    this->close();
}

void ViewEditer::on_btnApply_clicked()
{
    getConfigFromUI();

    _view->slot_ApplyConfig();
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

void ViewEditer::on_btnDeleteNode_clicked()
{
    QTreeWidgetItem* item = ui->treeMenuEdit->currentItem();
    if(item->text(1)==PluginIO::getInstance()->I_FunctionList[0]->_functonName)//暂时先别把自己删了
    {
        QMessageBox::information(this, tr("Infomation"), tr("Sorry! You have no authority to delete the item!"));
        return;
    }

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

void ViewEditer::on_btnAddNode_clicked()
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
    if(curSelItem==nullptr)//如果没有选中任何项，或者所选项为根节点，那就给这个根节点添加topLevelItem
        ui->treeMenuEdit->addTopLevelItem(item);
    else
        curSelItem->addChild(item);
}

void ViewEditer::on_btnUp_clicked()
{
    TreeItemMoveUp(ui->treeMenuEdit);
}

void ViewEditer::on_btnDown_clicked()
{
    TreeItemMoveDown(ui->treeMenuEdit);
}

void ViewEditer::on_btnLeft_clicked()
{
    TreeItemMoveLeft(ui->treeMenuEdit);
}

void ViewEditer::on_btnRight_clicked()
{
    TreeItemMoveRight(ui->treeMenuEdit);
}

void ViewEditer::on_btnAddAction_clicked()
{
    if(ui->treeMenuEdit->selectedItems().count()==0)
        return;

    if(ui->treeMenuEdit->currentItem()->text(0).contains("----------"))
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
            return;
        else
            ui->cbActionFromMenu_Toolbar->addItem(ce->_actionName);
    }
    delete  ce;
}

void ViewEditer::on_btnAddSeperator_clicked()
{
    QTreeWidgetItem* curSelItem= ui->treeMenuEdit->currentItem();
    if(curSelItem==nullptr || curSelItem->parent()==nullptr)//如果没有选中任何项，或者所选项为根节点，就不添加分隔符
        return;
    else
    {
        QTreeWidgetItem* seperator = new QTreeWidgetItem();
        seperator->setText(0, QStringLiteral("--------------------"));
        curSelItem->parent()->addChild(seperator);
    }
}

void ViewEditer::on_btnClearAction_clicked()
{
    QTreeWidgetItem* curSelItem= ui->treeMenuEdit->currentItem();

    for(int i=5; i<ui->treeMenuEdit->columnCount(); i++)
        curSelItem->setText(i, "");
}

void ViewEditer::on_btnIconFinder_clicked()
{
    if(ui->treeMenuEdit->currentItem()==nullptr)
        return;

    QString file_name = QFileDialog::getOpenFileName(this,
            tr("Open Icon File"),
            PluginIO::getInstance()->_core->I_ApplicationDirPath,
            "Images (*.png *.jpg *.bmp *.icon)",
            0);
        if (!file_name.isNull())
        {
            //fileName是文件名
            ui->treeMenuEdit->currentItem()->setText(2, file_name);
            ui->treeMenuEdit->currentItem()->setIcon(0, QIcon(file_name));
        }
        else{
            //点的是取消
            ui->treeMenuEdit->currentItem()->setIcon(0, QIcon());
        }
}

void ViewEditer::on_btnAddAction_Toolbar_clicked()
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

    if(tItem->parent() == nullptr)//说明是toplevelnode
    {
        QTreeWidgetItem* tChildItem = new QTreeWidgetItem();

        QIcon tIcon;
        foreach(QAction* act, _view->_actionList)
        {
            if(act->text()==ui->cbActionFromMenu_Toolbar->currentText())
            {
                tIcon = act->icon();
                break;
            }
        }
        tChildItem->setIcon(0, tIcon);
        tChildItem->setText(0, ui->cbActionFromMenu_Toolbar->currentText());
        tChildItem->setText(1, tr("Action"));
        tChildItem->setText(2, QString::number(ui->spanItemWidth_Toolbar->value()));
        tChildItem->setText(3, QString::number(ui->spanItemHeight_Toolbar->value()));
        tItem->addChild(tChildItem);
    }
    else
    {
        QMessageBox::information(this, tr("Infomation"), tr("Please select the toolbar node!"));
        return;
    }
}

void ViewEditer::on_btnAddSeperator_Toolbar_clicked()
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

    if(tItem->parent() == nullptr)//说明是toplevelnode
    {
        QTreeWidgetItem* tChildItem = new QTreeWidgetItem();
        tChildItem->setText(0, tr("--------------------"));
        tChildItem->setText(1, tr("Seperator"));
        tChildItem->setText(2, "");
        tChildItem->setText(3, "");
        tItem->addChild(tChildItem);
    }
    else
    {
        QMessageBox::information(this, tr("Infomation"), tr("Please select the toolbar node!"));
        return;
    }
}

void ViewEditer::on_btnAddWidget_Toolbar_clicked()
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
    PluginWidgetViewer* ce = new PluginWidgetViewer(plugInst->_core, this);
    ce->exec();

    if(ui->treeToolbarEdit->findItems(ce->_itemTag, Qt::MatchFlag::MatchExactly).count()>0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is a same action existed!"));
        return;
    }

    if(tItem->parent() == nullptr)//说明是toplevelnode
    {
        if(ce->_isOk)
        {
            QTreeWidgetItem* tChildItem = new QTreeWidgetItem();
            tChildItem->setText(0, ce->_itemTag);
            tChildItem->setText(1, tr("Widget"));
            tChildItem->setText(2, QString::number(ce->_widgetOrigWidth));
            tChildItem->setText(3, QString::number(ce->_widgetOrigHeight));
            tItem->addChild(tChildItem);
        }
    }
    else
    {
        QMessageBox::information(this, tr("Infomation"), tr("Please select the toolbar node!"));
        return;
    }
}

void ViewEditer::on_btnDeleteItem_Toolbar_clicked()
{
    if(ui->treeToolbarEdit->topLevelItemCount()==0)
        return;

    QTreeWidgetItem* tItem =  ui->treeToolbarEdit->currentItem();
    if(tItem==nullptr)
        return;

    if(tItem->parent()==nullptr)//说明是topLevelItem
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

        for(int i=0; i<ui->treeToolbarEdit->topLevelItemCount(); i++)
        {
            ui->treeToolbarEdit->topLevelItem(i)->setText(0, QString(tr("Bar%1")).arg(i+1));
        }
    }
    else//说明是ToolbarItem
    {
        del(tItem);
    }

}

void ViewEditer::TableItemMoveUp(QTableWidget *table)
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

void ViewEditer::TableItemMoveDown(QTableWidget *table)
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

void ViewEditer::TreeItemMoveUp(QTreeWidget* treeWidget)
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

void ViewEditer::TreeItemMoveDown(QTreeWidget* treeWidget)
{
    QTreeWidgetItem* curSelItem= treeWidget->currentItem();
    if(curSelItem==nullptr)
        return;

    if(curSelItem->parent()==nullptr)//toplevel
    {
        QTreeWidgetItem* topItem = curSelItem;

        int topIevelItemIndex = treeWidget->indexOfTopLevelItem(curSelItem);

        if(topIevelItemIndex>=treeWidget->topLevelItemCount())
            return;

        treeWidget->takeTopLevelItem(topIevelItemIndex);
        treeWidget->insertTopLevelItem(topIevelItemIndex, topItem);
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

void ViewEditer::TreeItemMoveLeft(QTreeWidget* treeWidget)
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
        if(grandpaNode==nullptr)//说明是第二级菜单
        {
            treeWidget->addTopLevelItem(copyItem);
            treeWidget->setCurrentItem(copyItem);
        }
        else//说明是三级及一下菜单
        {
            grandpaNode->addChild(copyItem);
            treeWidget->setCurrentItem(copyItem);
        }
    }
}

void ViewEditer::TreeItemMoveRight(QTreeWidget* treeWidget)
{
    QTreeWidgetItem* curSelItem= treeWidget->currentItem();
    if(curSelItem==nullptr)
        return;

    QTreeWidgetItem* copyItem = curSelItem;
    QTreeWidgetItem* parentNode = curSelItem->parent();

    if(parentNode==nullptr)//toplevel
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
                //不允许位于分割符或者action得下一级
                if(preParent->text(5)!="")
                {
                    QMessageBox::information(this, tr("Infomation"), tr("Cannot be at the next level of another node that is associated with an Action!"));
                    return;
                }

                if(preParent->text(0).contains("----------"))
                {
                    QMessageBox::information(this, tr("Infomation"), tr("Cannot be at the next level of a Seperator!"));
                    return;
                }

                parentNode->takeChild(itemIndex);
                parentNode->child(itemIndex-1)->addChild(copyItem);
                treeWidget->setCurrentItem(copyItem);
            }
        }
    }
}

void ViewEditer::on_btnMoveUp_Toolbar_clicked()
{
    TreeItemMoveUp(ui->treeToolbarEdit);
}

void ViewEditer::on_btnMoveDown_Toolbar_clicked()
{
    TreeItemMoveDown(ui->treeToolbarEdit);
}

void ViewEditer::on_btnAddWidget_Statusbar_clicked()
{
    PluginIO* plugInst = PluginIO::getInstance();
    PluginWidgetViewer* ce = new PluginWidgetViewer(plugInst->_core, this);
    ce->exec();


    if(ui->tableStatusbarEditer->findItems(ce->_itemTag, Qt::MatchFlag::MatchExactly).count()>0)
    {
        QMessageBox::information(this, tr("Infomation"), tr("There is a same action existed!"));
        return;
    }

    if(ce->_isOk)
    {
        int tRowCount = ui->tableStatusbarEditer->rowCount();
        ui->tableStatusbarEditer->insertRow(tRowCount);

        ui->tableStatusbarEditer->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(tRowCount+1)));
        ui->tableStatusbarEditer->setItem(tRowCount, 1, new QTableWidgetItem(ce->_itemTag));
        ui->tableStatusbarEditer->setItem(tRowCount, 2, new QTableWidgetItem(QString::number(ce->_widgetOrigWidth)));
        ui->tableStatusbarEditer->setItem(tRowCount, 3, new QTableWidgetItem(QString::number(ce->_widgetOrigHeight)));
    }
}

void ViewEditer::on_btnDeleteItem_Statusbar_clicked()
{
    int tRowIndex = ui->tableStatusbarEditer->currentRow();
    ui->tableStatusbarEditer->removeRow(tRowIndex);

    for(int i=tRowIndex; i<ui->tableStatusbarEditer->rowCount(); i++)
        ui->tableStatusbarEditer->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
}

void ViewEditer::on_btnMoveUp_Statusbar_clicked()
{
    TableItemMoveUp(ui->tableStatusbarEditer);
}

void ViewEditer::on_btnMoveDown_Statusbar_clicked()
{
    TableItemMoveDown(ui->tableStatusbarEditer);
}

void ViewEditer::on_btnAddToolbar_clicked()
{
    int tCurrTopNodeCount = ui->treeToolbarEdit->topLevelItemCount();
    QTreeWidgetItem* tTopNode = new QTreeWidgetItem();
    tTopNode->setText(0, QString(tr("Bar%1")).arg(tCurrTopNodeCount+1));
    ui->treeToolbarEdit->addTopLevelItem(tTopNode);
}

void ViewEditer::on_btnDeleteToolbar_clicked()
{
    QTreeWidgetItem* item =  ui->treeToolbarEdit->currentItem();
    if(item->parent()==nullptr)//说明是topLevelItem
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

ViewEditer *ViewEditer::getInstance()
{
    return instance;
}

void ViewEditer::slot_SelAllOrNot(bool flag)
{
    int row=0,col=0;
    int i=0,j=0;
    //row=ui->tablePluginLst->rowCount();
    foreach(PluginInterface* pi, ((QCPF_Interface*)_view->_core)->I_SysPlugins)
    {
        foreach (PluginWidgetInfo* pwi, pi->I_WidgetList) {
            row+=1;
        }
    }

    foreach(PluginInterface* pi, ((QCPF_Interface*)_view->_core)->I_NSysAllValidPlugins)
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
