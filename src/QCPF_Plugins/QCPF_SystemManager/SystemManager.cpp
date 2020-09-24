/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "SystemManager.h"
#include "ui_SystemManager.h"

#include "../../../interface/plugininterface.h"

#include <qstringliteral.h>

#include "utility/ccheckboxheaderview.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QStringLiteral>
#include <QTreeWidgetItem>
#include <QCheckBox>
#include "PluginIO.h"

SystemManager* sysMgrInstance;

SystemManager::SystemManager(QCPF_Model* model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemManager)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);

    _core = model;

    sysMgrInstance = this;
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
}

SystemManager::~SystemManager()
{
    delete ui;
}

void SystemManager::resizeEvent(QResizeEvent *event)
{
    //如果不是第一次显示
    if(!_isFirstResize)
        return;
    else
        _isFirstResize = false;
}

void SystemManager::showEvent(QShowEvent *event)
{
    _timer->start(1);
}

void SystemManager::slot_OnULoaded()
{
    setConfigToUI();
}

int SystemManager::setConfigToUI()
{
    //========================================================================
    //清空数据
    //========================================================================
    ui->tablePluginLst->clear();
    ui->tableOrigPluginsSort->clear();

    //读配置文件
    //_core->slot_LoadConfigFile(_core->_config);//model已经读过配置，因此这里不需要再读

    //========================================================================
    //设置样式
    //========================================================================
    //---------------------
    //设置原始组件信息列表
    //---------------------
    ui->tablePluginLst->setColumnCount(8);
    ui->tablePluginLst->setRowCount(0);

    QStringList nHeadLst;
    //如果下面出现乱码，就把环境设置为：
    //1.工具->选项->默认编码->UTF-8;
    //2.工具->选项->UTF-8 BOM->如果编码是UTF-8则添加
    nHeadLst<<""<<tr("No.")<<tr("Plugin ID")<<tr("Alias Name")<<tr("Tag")<<tr("Developor")<<tr("Version")<<tr("Detail");

    CCheckBoxHeaderView *myHeader = new CCheckBoxHeaderView(0, Qt::Horizontal, ui->tablePluginLst);
    ui->tablePluginLst->setHorizontalHeader(myHeader);

    ui->tablePluginLst->setHorizontalHeaderLabels(nHeadLst);

    ui->tablePluginLst->setColumnWidth(0, 30);
    ui->tablePluginLst->setColumnWidth(1, 40);
    ui->tablePluginLst->setColumnWidth(2, 120);
    ui->tablePluginLst->setColumnWidth(3, 100);
    ui->tablePluginLst->setColumnWidth(4, 260);
    ui->tablePluginLst->setColumnWidth(5, 80);
    ui->tablePluginLst->setColumnWidth(6, 80);
    ui->tablePluginLst->setColumnWidth(7, 150);

    setTableStyle(ui->tablePluginLst);

    //---------------------
    //设置原始组件排序表
    //---------------------
    ui->tableOrigPluginsSort->setColumnCount(2);
    ui->tableOrigPluginsSort->setRowCount(0);

    nHeadLst.clear();
    //如果下面出现乱码，就把环境设置为：
    //1.工具->选项->默认编码->UTF-8;
    //2.工具->选项->UTF-8 BOM->如果编码是UTF-8则添加
    nHeadLst<<tr("No.")<<tr("Plugin ID");

    ui->tableOrigPluginsSort->setHorizontalHeaderLabels(nHeadLst);

    ui->tableOrigPluginsSort->setColumnWidth(0, 50);
    ui->tableOrigPluginsSort->setColumnWidth(1, 150);

    setTableStyle(ui->tableOrigPluginsSort);
    //========================================================================
    //加载数据
    //========================================================================
    //---------------------
    //设置原始组件信息列表
    //---------------------
    int pluginCount = _core->I_SysPlugins.count();
    for(int i=0; i<pluginCount; i++)
    {
        QWidget *widget = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(this);
        QCheckBox *box = new QCheckBox(this);
        box->setObjectName(((Plugin_Interface *)_core->I_SysPlugins[i])->I_PluginID);

        layout->addWidget(box);
        layout->setMargin(0);
        layout->setAlignment(box,Qt::AlignCenter);
        widget->setLayout(layout);

        QString tOrigPluginID = ((Plugin_Interface *)_core->I_SysPlugins[i])->I_PluginID;

        //查找已选组件集合中是否已经有该项，如果有则设置选中状态，否则不选中
        int tIndex = -1;
        for(int i=0; i<_core->_config._sysPlugins_Sel.count(); i++)
        {
            if(_core->_config._sysPlugins_Sel[i]->_pluginID == tOrigPluginID)
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
        ui->tablePluginLst->setItem(tRowCount, 2, new QTableWidgetItem(((Plugin_Interface *)_core->I_SysPlugins[i])->I_PluginID));
        ui->tablePluginLst->setItem(tRowCount, 3, new QTableWidgetItem(((Plugin_Interface *)_core->I_SysPlugins[i])->I_PluginAliasName));
        ui->tablePluginLst->setItem(tRowCount, 4, new QTableWidgetItem(((Plugin_Interface *)_core->I_SysPlugins[i])->I_PluginTag.toString()));
        ui->tablePluginLst->setItem(tRowCount, 5, new QTableWidgetItem(((Plugin_Interface *)_core->I_SysPlugins[i])->I_PluginAuther));
        ui->tablePluginLst->setItem(tRowCount, 6, new QTableWidgetItem(((Plugin_Interface *)_core->I_SysPlugins[i])->I_PluginVersion));
        ui->tablePluginLst->setItem(tRowCount, 7, new QTableWidgetItem(((Plugin_Interface *)_core->I_SysPlugins[i])->I_PluginComment));

        box->setProperty("OrigPluginID",((Plugin_Interface *)_core->I_SysPlugins[i])->I_PluginID);
        box->setProperty("OrigPluginFilePath", ((Plugin_Interface *)_core->I_SysPlugins[i])->I_PluginFilePath);
    }

    //------------------------------
    //给原始组件排序列表中填充数据
    //------------------------------
    for(int i=0; i<_core->_config._sysPlugins_Sel.count(); i++)
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
            if(pluginID_OrigTable == _core->_config._sysPlugins_Sel[i]->_pluginID &&
               isChecked)
            {
                canShow = true;
                break;
            }
        }

        if(!canShow)
            continue;
        //======================================
        int tRowCount = ui->tableOrigPluginsSort->rowCount();
        ui->tableOrigPluginsSort->insertRow(tRowCount);

        ui->tableOrigPluginsSort->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(i+1)));
        ui->tableOrigPluginsSort->setItem(tRowCount, 1, new QTableWidgetItem(_core->_config._sysPlugins_Sel[i]->_pluginID));
    }

    //============================================
    //样式
    //============================================
    if(ui->tablePluginLst->rowCount()<=30)
        ui->tablePluginLst->setRowCount(30);

    //utility
    ui->txtSystemID->setText(_core->_config._systemID);
    ui->txtSystemName->setText(_core->_config._systemName);

    return 0;
}

void SystemManager::setTableStyle(QTableWidget *table)
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

SystemManager *SystemManager::getInstance()
{
    return sysMgrInstance;
}

void SystemManager::slot_SelAllOrNot(bool flag)
{
    int row=0,col=0;
    int i=0,j=0;
    //row=ui->tablePluginLst->rowCount();
    row = _core->I_SysPlugins.count();

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
 int SystemManager::getConfigFromUI()
 {
     //已选的系统组件，时序配置
     _core->_config._sysPlugins_Sel.clear();
     for(int i=0; i<ui->tableOrigPluginsSort->rowCount(); i++)
     {
         QString tOriginPluginID = ui->tableOrigPluginsSort->item(i, 1)->text();
         QString tFullFilePath;
         foreach (Plugin_Interface* pi, _core->I_SysPlugins) {
             if(pi->I_PluginID == tOriginPluginID)
             {
                tFullFilePath = pi->I_PluginFilePath;
                break;
             }
         }
         QString fileName = tFullFilePath.split("/").last();
         _core->_config._sysPlugins_Sel.append(new PluginInfo(_core->_config._this, tOriginPluginID, fileName));
     }
     _core->_config._count_sysPlugins_Sel = _core->_config._sysPlugins_Sel.count();//这个值若不给，序列化和反序列化时，将内存将无法对齐
     //-----------------------
    _core->_config._systemID = ui->txtSystemID->text();
    _core->_config._systemName = ui->txtSystemName->text();
     return 0;
 }

void SystemManager::on_btnOk_clicked()
{
    //====================================================================
    //保存配置(发送保存信号, 让_core自己进行存储自己的config信息)
    //====================================================================
    getConfigFromUI();

    emit sig_Save();
    this->close();
}

void SystemManager::on_btnCancel_clicked()
{
    emit sig_Cancel();
    this->close();
}

void SystemManager::on_pluginCheckbox_selChanged(int state)
{
    QCheckBox *chkBox = qobject_cast<QCheckBox *>(sender());
    QString origPluginID = chkBox->property("OrigPluginID").toString();
    QString origPluginFilePath = chkBox->property("OrigPluginFilePath").toString();

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

    //===============================================================================
    //如果原始组件被选中，则需要给tableOrigPluginsSort追加item，否则删除其他控件中与之关联的项
    if(chkBox->checkState() == Qt::CheckState::Checked)
    {
        if(tOrigPluginIndex==-1)
        {
            int tRowCount = ui->tableOrigPluginsSort->rowCount();
            ui->tableOrigPluginsSort->insertRow(tRowCount);

            ui->tableOrigPluginsSort->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(tRowCount + 1)));
            ui->tableOrigPluginsSort->setItem(tRowCount, 1, new QTableWidgetItem(origPluginID));
        }
    }
    else
    {
        int ret = QMessageBox::question(this, tr("info"), tr("Are you sure to uncheck this plugin and its copy?"));
        if(ret == QMessageBox::No)
        {
            chkBox->setChecked(true);
            return;
        }

        if(tOrigPluginIndex!=-1)
        {
            ui->tableOrigPluginsSort->removeRow(tOrigPluginIndex);
            for(int i=0; i<ui->tableOrigPluginsSort->rowCount(); i++)
                ui->tableOrigPluginsSort->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
        }
    }

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

void SystemManager::on_btnOrigPluginMoveUp_clicked()
{
    TableItemMoveUp(ui->tableOrigPluginsSort);
}

void SystemManager::on_btnOrigPluginMoveDown_clicked()
{
    TableItemMoveDown(ui->tableOrigPluginsSort);
}

void SystemManager::on_btnUpdate_clicked()
{
    tagOutputInfo info;
    info._type = INFT_PLUGIN_UPDATE;
    emit PluginIO::getInstance()->sig_OutputInfo(info);
}
