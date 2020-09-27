/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "PluginManager.h"
#include "ui_PluginManager.h"

#include "../../../interface/plugininterface.h"

#include <qstringliteral.h>

#include "utility/ccheckboxheaderview.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QStringLiteral>
#include <QTreeWidgetItem>
#include <QCheckBox>
#include "PluginIO.h"

PluginManager* pMgrInstance;

PluginManager::PluginManager(QCPF_Model* model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginManager)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);

    _core = model;

    pMgrInstance = this;
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
    setMinimumSize(QSize(950, 670));
    setMaximumSize(QSize(950, 670));
    setSizeGripEnabled(false);

    connect(this, SIGNAL(sig_Save(void)), _core, SLOT(slot_SaveConfigFile(void)));
    connect(this, SIGNAL(sig_Cancel(void)), _core, SLOT(slot_CancelConfig(void)));
    connect(this, SIGNAL(sig_Apply(void)), _core, SLOT(slot_ApplyConfig(void)));

    //注册面板显示后的信号槽
    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnULoaded()));

    ui->btnOk->setFocus();
    ui->btnOk->setDefault(true);
}

PluginManager::~PluginManager()
{
    delete ui;
}

void PluginManager::resizeEvent(QResizeEvent *event)
{
    //如果不是第一次显示
    if(!_isFirstResize)
        return;
    else
        _isFirstResize = false;
}

void PluginManager::showEvent(QShowEvent *event)
{
    _timer->start(1);
}

void PluginManager::slot_OnULoaded()
{
    setConfigToUI();
}

int PluginManager::setConfigToUI()
{
    //========================================================================
    //清空数据
    //========================================================================
    ui->cbOriginPluginLst->clear();
    ui->treePluginClone->clear();
    ui->tablePluginLst->clear();
    ui->tableOrigPluginsSort->clear();
    ui->tableAllValidPluginsSort->clear();

    //读配置文件
    //_core->slot_LoadConfigFile(_core->_config);//model已经读过配置，因此这里不需要再读

    //========================================================================
    //设置样式
    //========================================================================
    //--------------------------
    //设置原始组件信息列表样式
    //--------------------------
    QStringList nHeadLst;
    ui->tablePluginLst->setColumnCount(9);
    ui->tablePluginLst->setRowCount(0);

    //如果下面出现乱码，就把环境设置为：
    //1.工具->选项->默认编码->UTF-8;
    //2.工具->选项->UTF-8 BOM->如果编码是UTF-8则添加
    nHeadLst<<""<<tr("No.")<<tr("Plugin ID")<<tr("Plugin Alias")<<tr("Plugin Tag")<<tr("Developer")<<tr("Version")<<tr("Detail")<<tr("Path");

    CCheckBoxHeaderView *myHeader = new CCheckBoxHeaderView(0, Qt::Horizontal, ui->tablePluginLst);
    ui->tablePluginLst->setHorizontalHeader(myHeader);

    ui->tablePluginLst->setHorizontalHeaderLabels(nHeadLst);

    ui->tablePluginLst->setColumnWidth(0, 30);
    ui->tablePluginLst->setColumnWidth(1, 40);
    ui->tablePluginLst->setColumnWidth(2, 100);
    ui->tablePluginLst->setColumnWidth(3, 100);
    ui->tablePluginLst->setColumnWidth(4, 250);
    ui->tablePluginLst->setColumnWidth(5, 70);
    ui->tablePluginLst->setColumnWidth(6, 70);
    ui->tablePluginLst->setColumnWidth(7, 120);
    ui->tablePluginLst->setColumnWidth(8, 120);

    setTableStyle(ui->tablePluginLst);

    //--------------------------
    //设置原始组件排序表样式
    //--------------------------
    ui->tableOrigPluginsSort->setColumnCount(3);
    ui->tableOrigPluginsSort->setRowCount(0);

    nHeadLst.clear();
    //如果下面出现乱码，就把环境设置为：
    //1.工具->选项->默认编码->UTF-8;
    //2.工具->选项->UTF-8 BOM->如果编码是UTF-8则添加
    nHeadLst<<tr("No.")<<tr("Plugin ID")<<tr("Path");

    ui->tableOrigPluginsSort->setHorizontalHeaderLabels(nHeadLst);

    ui->tableOrigPluginsSort->setColumnWidth(0, 40);
    ui->tableOrigPluginsSort->setColumnWidth(1, 150);
    ui->tableOrigPluginsSort->setColumnWidth(2, 150);

    setTableStyle(ui->tableOrigPluginsSort);

    //--------------------------
    //设置所有可用组件排序表样式
    //--------------------------
    ui->tableAllValidPluginsSort->setColumnCount(4);
    ui->tableAllValidPluginsSort->setRowCount(0);

    nHeadLst.clear();
    //如果下面出现乱码，就把环境设置为：
    //1.工具->选项->默认编码->UTF-8;
    //2.工具->选项->UTF-8 BOM->如果编码是UTF-8则添加
    nHeadLst<<tr("No")<<tr("Plugin ID")<<tr("Copy ID")<<tr("Plugin Type");

    ui->tableAllValidPluginsSort->setHorizontalHeaderLabels(nHeadLst);

    ui->tableAllValidPluginsSort->setColumnWidth(0, 40);
    ui->tableAllValidPluginsSort->setColumnWidth(1, 150);
    ui->tableAllValidPluginsSort->setColumnWidth(2, 150);
    ui->tableAllValidPluginsSort->setColumnWidth(3, 150);

    setTableStyle(ui->tableAllValidPluginsSort);

    //========================================================================
    //加载数据
    //========================================================================

    //--------------------------
    //为原始组件信息列表加载数据
    //--------------------------
    int pluginCount = _core->I_NSysOrigPlugins.count();
    for(int i=0; i<pluginCount; i++)
    {
        QWidget *widget = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(this);
        QCheckBox *box = new QCheckBox(this);
        box->setObjectName(((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginID);

        layout->addWidget(box);
        layout->setMargin(0);
        layout->setAlignment(box,Qt::AlignCenter);
        widget->setLayout(layout);

        QString tOrigPluginID = ((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginID;

        //查找已选组件集合中是否已经有该项，如果有则设置选中状态，否则不选中
        int tIndex = -1;
        for(int i=0; i<_core->_config._nSysPlugins_Sel.count(); i++)
        {
            if(_core->_config._nSysPlugins_Sel[i]->_pluginID == tOrigPluginID)
            {
                tIndex = i;
                break;
            }
        }

        if(-1==tIndex)
            box->setChecked(false);
        else
            box->setChecked(true);

        connect(box, SIGNAL(stateChanged(int)), this, SLOT(on_pluginCheckbox_selChanged(int)));

        int tRowCount = ui->tablePluginLst->rowCount();
        ui->tablePluginLst->insertRow(tRowCount);

        ui->tablePluginLst->setCellWidget(tRowCount, 0, widget);//插入复选框
        ui->tablePluginLst->setItem(tRowCount, 1, new QTableWidgetItem(QString::number(i+1)));
        ui->tablePluginLst->setItem(tRowCount, 2, new QTableWidgetItem(((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginID));
        ui->tablePluginLst->setItem(tRowCount, 3, new QTableWidgetItem(((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginAliasName));
        ui->tablePluginLst->setItem(tRowCount, 4, new QTableWidgetItem(((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginTag.toString()));
        ui->tablePluginLst->setItem(tRowCount, 5, new QTableWidgetItem(((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginAuther));
        ui->tablePluginLst->setItem(tRowCount, 6, new QTableWidgetItem(((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginVersion));
        ui->tablePluginLst->setItem(tRowCount, 7, new QTableWidgetItem(((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginComment));
        ui->tablePluginLst->setItem(tRowCount, 8, new QTableWidgetItem(((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginFilePath));

        box->setProperty("OrigPluginID",((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginID);
        box->setProperty("OrigPluginFilePath", ((Plugin_Interface *)_core->I_NSysOrigPlugins[i])->I_PluginFilePath);
    }

    //=============================================
    //设置克隆组件树, 遍历I_nSysAllValidPlugins，这样可以保证加载顺序与排序一致
    //=============================================
    //--------------------------
    //设置克隆树样式
    //--------------------------
    ui->treePluginClone->setColumnCount(4);
    nHeadLst.clear();
    nHeadLst<<tr("Original Plugin ID")<<QStringLiteral("Copy ID")<<QStringLiteral("Copy Alias")<<QStringLiteral("Copy Detail");
    ui->treePluginClone->setHeaderLabels(nHeadLst);

    ui->treePluginClone->setColumnWidth(0, 120);
    ui->treePluginClone->setColumnWidth(1, 120);
    ui->treePluginClone->setColumnWidth(2, 120);
    ui->treePluginClone->setColumnWidth(3, 150);
    //设置表头颜色
    ui->treePluginClone->header()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
    ui->treePluginClone->header()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter); //居中
    ui->treePluginClone->header()->setStretchLastSection(true);
    ui->treePluginClone->setStyleSheet( "QTreeView::item:hover{background-color:rgb(110,178,233); color:white}"
    "QTreeView::item:selected{background-color:rgb(0,120,215)}"
    "QTreeView::item:selected{color: white}"
    "QTreeWidget::item{border-right: 1px solid silver; font:9pt '微软雅黑';}"
     );
    //--------------------------
    //为克隆树加载数据
    //--------------------------
    foreach(ClonePluginInfo *tp, _core->_config._nSysClonePlugins)
    {
        //find the item from origin plugin list
        bool canShow = false;
        for(int j=0; j<ui->tablePluginLst->rowCount(); j++)
        {
            QString pluginID_OrigTable = ui->tablePluginLst->item(j, 2)->text();
            bool isChecked = false;
            if (QWidget *w = ui->tablePluginLst->cellWidget(j, 0))//先获取widget
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  //通过children来访问checkbox
                isChecked = checkBox->checkState()==2?true:false;
            }
            //if pluginId in the origin talbe and it's checked, then insert the item to talbOriginPluginSort
            if(pluginID_OrigTable == tp->_originalPluginID &&
               isChecked)
            {
                canShow = true;
                break;
            }
        }

        if(!canShow)
            continue;
        //======================================
        int tIndex = -1;
        QTreeWidgetItem *origRootItem = nullptr;
        for(int i=0; i<ui->treePluginClone->topLevelItemCount(); i++)
        {
            if(ui->treePluginClone->topLevelItem(i)->text(0) == tp->_originalPluginID)
            {
                tIndex = i;
                origRootItem = ui->treePluginClone->topLevelItem(i);
                break;
            }
        }

        if(tIndex==-1)
        {
            QTreeWidgetItem *tTopItem = new QTreeWidgetItem();
            tTopItem->setText(0, tp->_originalPluginID);
            ui->treePluginClone->addTopLevelItem(tTopItem);
            origRootItem = tTopItem;
        }

        QTreeWidgetItem *tCloneItem = new QTreeWidgetItem();
        tCloneItem->setText(1, tp->_copyID);
        tCloneItem->setText(2, tp->_copyAliasName);
        tCloneItem->setText(3, tp->_copyComment);

        origRootItem->addChild(tCloneItem);
    }
    ui->treePluginClone->repaint();
    ui->treePluginClone->expandAll();

    //加载原始组件的时候，就会自动给cbOriginPluginLst中添加item
    for(int i=0; i<_core->_config._nSysPlugins_Sel.count(); i++)
    {
        //find the item from origin plugin list
        bool canShow = false;
        for(int j=0; j<ui->tablePluginLst->rowCount(); j++)
        {
            QString pluginID_OrigTable = ui->tablePluginLst->item(j, 2)->text();
            bool isChecked = false;
            if (QWidget *w = ui->tablePluginLst->cellWidget(j, 0))//先获取widget
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  //通过children来访问checkbox
                isChecked = checkBox->checkState()==2?true:false;
            }
            //if pluginId in the origin talbe and it's checked, then insert the item to talbOriginPluginSort
            if(pluginID_OrigTable == _core->_config._nSysPlugins_Sel[i]->_pluginID &&
               isChecked)
            {
                canShow = true;
                break;
            }
        }

        if(!canShow)
            continue;
        //================================================
        ui->cbOriginPluginLst->addItem(_core->_config._nSysPlugins_Sel[i]->_pluginID);
    }

    //给原始组件排序列表中填充数据
    for(int i=0; i<_core->_config._nSysPlugins_Sel.count(); i++)
    {
        //find the item from origin plugin list
        bool canShow = false;
        for(int j=0; j<ui->tablePluginLst->rowCount(); j++)
        {
            QString pluginID_OrigTable = ui->tablePluginLst->item(j, 2)->text();
            bool isChecked = false;
            if (QWidget *w = ui->tablePluginLst->cellWidget(j, 0))//先获取widget
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  //通过children来访问checkbox
                isChecked = checkBox->checkState()==2?true:false;
            }
            //if pluginId in the origin talbe and it's checked, then insert the item to talbOriginPluginSort
            if(pluginID_OrigTable == _core->_config._nSysPlugins_Sel[i]->_pluginID &&
               isChecked)
            {
                canShow = true;
                break;
            }
        }

        if(!canShow)
            continue;
        //====================================================
        int tRowCount = ui->tableOrigPluginsSort->rowCount();
        ui->tableOrigPluginsSort->insertRow(tRowCount);

        ui->tableOrigPluginsSort->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(i+1)));
        ui->tableOrigPluginsSort->setItem(tRowCount, 1, new QTableWidgetItem(_core->_config._nSysPlugins_Sel[i]->_pluginID));
        ui->tableOrigPluginsSort->setItem(tRowCount, 2, new QTableWidgetItem(_core->I_NonSysPluginDirPath + _core->_config._nSysPlugins_Sel[i]->_pluginFileName));
    }

    //给所有原始组件和克隆组件表填充数据
    for(int i=0; i<_core->_config._nSysAllValidPlugins.count(); i++)
    {
        //find the item from origin plugin list
        bool canShow = false;
        for(int j=0; j<ui->tablePluginLst->rowCount(); j++)
        {
            QString pluginID_OrigTable = ui->tablePluginLst->item(j, 2)->text();
            bool isChecked = false;
            if (QWidget *w = ui->tablePluginLst->cellWidget(j, 0))//先获取widget
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  //通过children来访问checkbox
                isChecked = checkBox->checkState()==2?true:false;
            }
            //if pluginId in the origin talbe and it's checked, then insert the item to talbOriginPluginSort
            if(pluginID_OrigTable == _core->_config._nSysAllValidPlugins[i]->_originalPluginID &&
               isChecked)
            {
                canShow = true;
                break;
            }
        }

        if(!canShow)
            continue;
        //====================================================

        int tRowCount = ui->tableAllValidPluginsSort->rowCount();
        ui->tableAllValidPluginsSort->insertRow(tRowCount);

        ui->tableAllValidPluginsSort->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(i+1)));
        ui->tableAllValidPluginsSort->setItem(tRowCount, 1, new QTableWidgetItem(_core->_config._nSysAllValidPlugins[i]->_originalPluginID));
        ui->tableAllValidPluginsSort->setItem(tRowCount, 2, new QTableWidgetItem(_core->_config._nSysAllValidPlugins[i]->_copyID));
        ui->tableAllValidPluginsSort->setItem(tRowCount, 3, new QTableWidgetItem(_core->_config._nSysAllValidPlugins[i]->_isCopy?tr("Copy"):tr("Original")));
    }

    //=============================================
    //设置其他参数
    //=============================================

    //============================================
    //样式
    //============================================
    if(ui->tablePluginLst->rowCount()<=30)
        ui->tablePluginLst->setRowCount(30);

    return 0;
}

void PluginManager::setTableStyle(QTableWidget *table)
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

PluginManager *PluginManager::getInstance()
{
    return pMgrInstance;
}

void PluginManager::slot_SelAllOrNot(bool flag)
{
    int row=0,col=0;
    int i=0,j=0;
    //row=ui->tablePluginLst->rowCount();
    row = _core->I_NSysOrigPlugins.count();

    if(flag == true)
    {
        for(;i<row;i++)
        {
            if (QWidget *w = ui->tablePluginLst->cellWidget(i, 0))//先获取widget
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  //通过children来访问checkbox
                checkBox->setChecked(true);
            }
        }
    }
    else
    {
        for(;i<row;i++)
        {
            if (QWidget *w = ui->tablePluginLst->cellWidget(i, 0))//先获取widget
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  //通过children来访问checkbox
                checkBox->setChecked(false);
            }
        }
    }

}
 int PluginManager::getConfigFromUI()
 {
     //====================================================================
     //内核配置项赋值
     //====================================================================

     //已选的原始组件，时序配置
     _core->_config._nSysPlugins_Sel.clear();
     for(int i=0; i<ui->tableOrigPluginsSort->rowCount(); i++)
     {
         QString tOriginPluginID = ui->tableOrigPluginsSort->item(i, 1)->text();
         QString tOriginPluginFileName = ui->tableOrigPluginsSort->item(i, 2)->text().split("/").last();
         if(tOriginPluginFileName=="" || tOriginPluginID=="")
             continue;
         _core->_config._nSysPlugins_Sel.append(new PluginInfo(_core->_config._this, tOriginPluginID, tOriginPluginFileName));
     }
     _core->_config._count_nSysPlugins_Sel = _core->_config._nSysPlugins_Sel.count();//这个值若不给，序列化和反序列化时，将内存将无法对齐

     //克隆配置
     _core->_config._nSysClonePlugins.clear();
     for (int i=0; i<ui->treePluginClone->topLevelItemCount(); i++)
     {
         QString tOrigPluginID = ui->treePluginClone->topLevelItem(i)->text(0);
         for(int j=0; j<ui->treePluginClone->topLevelItem(i)->childCount(); j++)
         {
             QString tCopyID = ui->treePluginClone->topLevelItem(i)->child(j)->text(1);
             QString tCopyAliasName = ui->treePluginClone->topLevelItem(i)->child(j)->text(2);
             QString tCopyComment = ui->treePluginClone->topLevelItem(i)->child(j)->text(3);

             _core->_config._nSysClonePlugins.append(new ClonePluginInfo(_core->_config._this, tOrigPluginID, tCopyID, tCopyAliasName, tCopyComment));
         }
     }
     _core->_config._count_nSysClonePlugins = _core->_config._nSysClonePlugins.count();//这个值若不给，序列化和反序列化时，将内存将无法对齐

     //所有组件顺序配置
     _core->_config._nSysAllValidPlugins.clear();
     for(int i=0; i<ui->tableAllValidPluginsSort->rowCount(); i++)
     {
         QString tOrigPluginID = ui->tableAllValidPluginsSort->item(i, 1)->text();
         QString tCopyID = ui->tableAllValidPluginsSort->item(i, 2)->text();
         bool tIsCopy = tCopyID==""?false:true;
         _core->_config._nSysAllValidPlugins.append(new ValidPluginInfo(_core->_config._this, tOrigPluginID, tCopyID, tIsCopy));
     }
     _core->_config._count_nSysAllValidPlugins = _core->_config._nSysAllValidPlugins.count();//这个值若不给，序列化和反序列化时，内存将无法对齐

     //------------

     //====================================================================
     //框架配置项赋值
     //====================================================================
     //((MainWindow*)this->parent())->setWindowTitle(ui->txtSystemName->text());
     return 0;
 }

void PluginManager::on_btnOk_clicked()
{
    //====================================================================
    //保存配置(发送保存信号, 让_core自己进行存储自己的config信息)
    //====================================================================
    getConfigFromUI();
    emit sig_Save();
    this->close();

}

void PluginManager::on_btnCancel_clicked()
{
    emit sig_Cancel();
    this->close();
}

void PluginManager::on_btnClone_clicked()
{
    if(ui->cbOriginPluginLst->children().count()==0)
    {
        QMessageBox::information(this, tr("info"), tr("No valid plugins!"));
        return;
    }

    if(ui->txtCopyAliasName->text().trimmed()=="")
    {
        QMessageBox::information(this, tr("info"), tr("Copy alias can not be null!"));
        return;
    }

    foreach(Plugin_Interface* pi, _core->I_NSysOrigPlugins_Sel){
        QString tTagStr = pi->I_PluginTag.value<QString>();
        if(tTagStr==nullptr)
        {
            QMessageBox::information(this, tr("info"), tr("Plugin tag is invalid!"));
            return;
        }

        QStringList tTagLst = tTagStr.split("\\");
        if(tTagLst.count()>=1 && tTagLst.first()==QStringLiteral("SINGLETON"))
        {
            QMessageBox::information(this, tr("info"), tr("a singleton plugin can not be cloned!"));
            return;
        }
    }

    QString tOrigPluginID = ui->cbOriginPluginLst->currentText();
    QString tCopyID = ui->txtCopyID->text();
    QString tCopyAliasName = ui->txtCopyAliasName->text();
    QString tCopyComment = ui->txtCopyComment->toPlainText();

    //查找是否已经存在item
    for(int i=0; i<ui->treePluginClone->topLevelItemCount(); i++)
    {
        for(int j=0; j<ui->treePluginClone->topLevelItem(i)->childCount(); j++)
        {
            if(ui->treePluginClone->topLevelItem(i)->text(0) == tOrigPluginID && ui->treePluginClone->topLevelItem(i)->child(j)->text(1) == tCopyID)
            {
                QMessageBox::information(this, tr("info"), tr("the same CopyID = \"")+tCopyID+QStringLiteral("\" already exists!"));
                return;
            }
        }
    }

    //遍历树根集合，查找目标根
    QTreeWidgetItem* tOrigItem = nullptr;
    for(int i=0; i<ui->treePluginClone->topLevelItemCount(); i++)
    {
        if(ui->treePluginClone->topLevelItem(i)->text(0) == tOrigPluginID)
        {
            tOrigItem = ui->treePluginClone->topLevelItem(i);
            break;
        }
    }

    //如果有目标根，就直接追加，否则就新建目标根
    if(tOrigItem==nullptr)
    {
        tOrigItem = new QTreeWidgetItem();
        tOrigItem->setText(0, tOrigPluginID);
        ui->treePluginClone->addTopLevelItem(tOrigItem);
    }

    QTreeWidgetItem* tCloneItem = new QTreeWidgetItem();
    tCloneItem->setText(1, tCopyID);
    tCloneItem->setText(2, tCopyAliasName);
    tCloneItem->setText(3, tCopyComment);

    if(tOrigItem!=nullptr)
    {
        tOrigItem->addChild(tCloneItem);
    }
    ui->treePluginClone->repaint();
    ui->treePluginClone->expandAll();
    //------------------------------向所有组件表里添加数据。
    int tRowCount = ui->tableAllValidPluginsSort->rowCount();
    ui->tableAllValidPluginsSort->insertRow(tRowCount);

    ui->tableAllValidPluginsSort->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(tRowCount+1)));
    ui->tableAllValidPluginsSort->setItem(tRowCount, 1, new QTableWidgetItem(tOrigPluginID));
    ui->tableAllValidPluginsSort->setItem(tRowCount, 2, new QTableWidgetItem(tCopyID));
    ui->tableAllValidPluginsSort->setItem(tRowCount, 3, new QTableWidgetItem(tr("Copy")));
}

void PluginManager::on_btnDeleteClone_clicked()
{
    QTreeWidgetItem *tItem = ui->treePluginClone->currentItem();
    if(tItem==nullptr)
        return;

    if(""==tItem->text(0))//说明是子项
    {
        //如果该子节点的父节点只有它这一个项，则直接删除父节点
        if(tItem->parent()->childCount()==1)
        {
            int tIndex=-1;
            for(int i=0; i<ui->treePluginClone->topLevelItemCount(); i++)
            {
                if(ui->treePluginClone->topLevelItem(i)->text(0) == tItem->parent()->text(0))
                {
                    tIndex = i;
                    break;
                }
            }

            if(tIndex!=-1)
                ui->treePluginClone->takeTopLevelItem(tIndex);
        }
        else
            tItem->parent()->removeChild(tItem);
    }
    else//如果选择的是根节点，则删除这个根节点
    {
        int tIndex=-1;
        for(int i=0; i<ui->treePluginClone->topLevelItemCount(); i++)
        {
            if(ui->treePluginClone->topLevelItem(i)->text(0) == tItem->text(0))
            {
                tIndex = i;
                break;
            }
        }

        if(tIndex!=-1)
            ui->treePluginClone->takeTopLevelItem(tIndex);
    }
    //===============================对tableAllValidPluginLst做出更新
   for(int i=ui->tableAllValidPluginsSort->rowCount()-1; i>=0; i--)//在tableAllValidPluginLst中，按从上到下的顺序找出克隆组件，然后再到克隆树上看有没有这个克隆体，如果没有就直接把它删掉。
   {
       QString tItemCloneID = ui->tableAllValidPluginsSort->item(i, 2)->text();
       if(tItemCloneID!="")
       {
           QList<QTreeWidgetItem*> itemLst = ui->treePluginClone->findItems(tItemCloneID, Qt::MatchFlag::MatchRecursive | Qt::MatchFlag::MatchExactly, 1);

           //成立说明在克隆树上没找到这个克隆体
           if(itemLst.count()==0)
               ui->tableAllValidPluginsSort->removeRow(i);
       }
   }

}

void PluginManager::on_pluginCheckbox_selChanged(int state)
{
    QCheckBox *chkBox = qobject_cast<QCheckBox *>(sender());
    QString origPluginID = chkBox->property("OrigPluginID").toString();
    QString origPluginFilePath = chkBox->property("OrigPluginFilePath").toString();

    //在cbOriginPluginLst查看是否已经存在原始组件item
    int tCbIndex = -1;
    tCbIndex = ui->cbOriginPluginLst->findText(origPluginID);

    //在克隆树上的第一列查找符合条件的根节点
    int tTreeTopItemIndex = -1;
    for(int i=0; i<ui->treePluginClone->topLevelItemCount(); i++)
    {
        if(ui->treePluginClone->topLevelItem(i)->text(0) == origPluginID)
        {
            tTreeTopItemIndex = i;
            break;
        }
    }

    //在tableOrigPluginsSort查看是否已经存在原始组件item
    int tOrigPluginIndex = -1;
    for(int i=0; i<ui->tableOrigPluginsSort->rowCount(); i++)
    {
        if(ui->tableOrigPluginsSort->item(i, 1)->text()==origPluginID)
        {
            tOrigPluginIndex = i;
            break;
        }
    }

    //在tableAllValidPluginsSort查看是否已经存在原始组件item
    int tAllValidOrigPluginIndex = -1;//在所有可用组件列表中，目标原始组件的索引
    QList<int> tAllValidPluginIndexLst;//在所有可用组件列表中，目标原始组件及其克隆体的索引集合
    for(int i=0; i<ui->tableAllValidPluginsSort->rowCount(); i++)
    {
        if(ui->tableAllValidPluginsSort->item(i, 1)->text()==origPluginID)
        {
            tAllValidPluginIndexLst.append(i);
            if(ui->tableAllValidPluginsSort->item(i, 2)->text()==QStringLiteral(""))
            {
                tAllValidOrigPluginIndex = i;
            }
        }
    }

    //===============================================================================
    //如果原始组件被选中，则需要分别给cbOriginPluginLst, tableOrigPluginsSort和tableAllValidPluginsSort追加item，否则删除其他控件中与之关联的项
    if(chkBox->checkState() == Qt::CheckState::Checked)
    {
        if(tCbIndex==-1)
            ui->cbOriginPluginLst->addItem(origPluginID);

        if(tOrigPluginIndex==-1)
        {
            int tRowCount = ui->tableOrigPluginsSort->rowCount();
            ui->tableOrigPluginsSort->insertRow(tRowCount);

            ui->tableOrigPluginsSort->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(tRowCount + 1)));
            ui->tableOrigPluginsSort->setItem(tRowCount, 1, new QTableWidgetItem(origPluginID));
            ui->tableOrigPluginsSort->setItem(tRowCount, 2, new QTableWidgetItem(origPluginFilePath));
        }

        if(tAllValidOrigPluginIndex==-1)
        {
            int tRowCount = ui->tableAllValidPluginsSort->rowCount();
            ui->tableAllValidPluginsSort->insertRow(tRowCount);

            ui->tableAllValidPluginsSort->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(tRowCount + 1)));
            ui->tableAllValidPluginsSort->setItem(tRowCount, 1, new QTableWidgetItem(origPluginID));
            ui->tableAllValidPluginsSort->setItem(tRowCount, 2, new QTableWidgetItem(tr("")));
            ui->tableAllValidPluginsSort->setItem(tRowCount, 3, new QTableWidgetItem(tr("Original")));
        }
    }
    else
    {
        int ret = QMessageBox::question(this, tr("info!"), tr("Are you sure to uncheck this plugin and its copy?"));
        if(ret == QMessageBox::No)
        {
            chkBox->setChecked(true);
            return;
        }

        if(tCbIndex!=-1)
            ui->cbOriginPluginLst->removeItem(tCbIndex);

        if(tTreeTopItemIndex !=-1)
            ui->treePluginClone->takeTopLevelItem(tTreeTopItemIndex);

        if(tOrigPluginIndex!=-1)
        {
            ui->tableOrigPluginsSort->removeRow(tOrigPluginIndex);
            for(int i=0; i<ui->tableOrigPluginsSort->rowCount(); i++)
                ui->tableOrigPluginsSort->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
        }

        //倒着删，否则顺序对不上
        for(int i=tAllValidPluginIndexLst.count()-1; i>=0; i--)
        {
            ui->tableAllValidPluginsSort->removeRow(tAllValidPluginIndexLst[i]);
        }
        //重新编号
        for(int i=0; i<ui->tableAllValidPluginsSort->rowCount(); i++)
            ui->tableAllValidPluginsSort->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
    }
}

void PluginManager::on_treePluginClone_itemPressed(QTreeWidgetItem *item, int column)
{
    //只要点过一下就使能删除克隆按钮
    ui->btnDeleteClone->setEnabled(true);
}

void PluginManager::on_cbOriginPluginLst_currentIndexChanged(int index)
{
    ui->txtCopyID->clear();
    ui->txtCopyAliasName->clear();
    ui->txtCopyComment->clear();
}

void TableItemMoveUp(QTableWidget *table)
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

void TableItemMoveDown(QTableWidget *table)
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

void PluginManager::on_btnOrigPluginMoveUp_clicked()
{
    TableItemMoveUp(ui->tableOrigPluginsSort);
}

void PluginManager::on_btnOrigPluginMoveDown_clicked()
{
    TableItemMoveDown(ui->tableOrigPluginsSort);
}

void PluginManager::on_btnValidPluginMoveUp_clicked()
{
    TableItemMoveUp(ui->tableAllValidPluginsSort);
}

void PluginManager::on_btnValidPluginMoveDown_clicked()
{
    TableItemMoveDown(ui->tableAllValidPluginsSort);
}

void PluginManager::on_btnRefreshPlugins_clicked()
{
    tagOutputInfo info;
    info._type = INFT_PLUGIN_COLLECT;
    emit PluginIO::getInstance()->sig_OutputInfo(info);
}
