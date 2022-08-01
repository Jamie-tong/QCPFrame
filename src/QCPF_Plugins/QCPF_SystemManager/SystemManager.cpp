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
    connect(this,SIGNAL(sig_SelAllOrNot(bool)),this,SLOT(slot_SelAllOrNot(bool)));

    setWindowFlags(Qt::Dialog
                   | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    setMinimumSize(QSize(950, 666));

    setSizeGripEnabled(true);

    connect(this, SIGNAL(sig_Save(void)), _core, SLOT(slot_SaveConfigFile(void)));
    connect(this, SIGNAL(sig_Cancel(void)), _core, SLOT(slot_CancelConfig(void)));
    connect(this, SIGNAL(sig_Apply(void)), _core, SLOT(slot_ApplyConfig(void)));

    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnULoaded()));

    ui->btnOk->setFocus();
    ui->btnOk->setDefault(true);
}

SystemManager::~SystemManager()
{
    delete ui;
}

void SystemManager::resizeEvent(QResizeEvent *event)
{
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
    ui->tablePluginLst->clear();
    ui->tableOrigPluginsSort->clear();

    ui->tablePluginLst->setColumnCount(8);
    ui->tablePluginLst->setRowCount(0);

    QStringList nHeadLst;

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

    ui->tableOrigPluginsSort->setColumnCount(2);
    ui->tableOrigPluginsSort->setRowCount(0);

    nHeadLst.clear();

    nHeadLst<<tr("No.")<<tr("Plugin ID");

    ui->tableOrigPluginsSort->setHorizontalHeaderLabels(nHeadLst);

    ui->tableOrigPluginsSort->setColumnWidth(0, 50);
    ui->tableOrigPluginsSort->setColumnWidth(1, 150);

    setTableStyle(ui->tableOrigPluginsSort);

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

        ui->tablePluginLst->setCellWidget(tRowCount, 0, widget);
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

    for(int i=0; i<_core->_config._sysPlugins_Sel.count(); i++)
    {
        bool canShow = false;
        for(int j=0; j<ui->tablePluginLst->rowCount(); j++)
        {
            QString pluginID_OrigTable = ui->tablePluginLst->item(j, 2)->text();
            bool isChecked = false;
            if (QWidget *w = ui->tablePluginLst->cellWidget(j, 0))
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));
                isChecked = checkBox->checkState()==2?true:false;
            }
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

    if(ui->tablePluginLst->rowCount()<=30)
        ui->tablePluginLst->setRowCount(30);

    ui->txtSystemID->setText(_core->_config._systemID);
    ui->txtSystemName->setText(_core->_config._systemName);

    ui->chkEnableHotPlug->setCheckState(_core->_config._enableHotPlug?(Qt::CheckState::Checked):(Qt::CheckState::Unchecked));
    return 0;
}

void SystemManager::setTableStyle(QTableWidget *table)
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

SystemManager *SystemManager::getInstance()
{
    return sysMgrInstance;
}

void SystemManager::slot_SelAllOrNot(bool flag)
{
    int row=0,col=0;
    int i=0,j=0;

    row = _core->I_SysPlugins.count();

    if(flag == true)
    {
        for(;i<row;i++)
        {
            if (QWidget *w = ui->tablePluginLst->cellWidget(i, 0))
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));
                checkBox->setChecked(true);
            }
        }
    }
    else
    {
        for(;i<row;i++)
        {
            if (QWidget *w = ui->tablePluginLst->cellWidget(i, 0))
            {
                QCheckBox * checkBox = qobject_cast<QCheckBox*>(w->children().at(1));
                checkBox->setChecked(false);
            }
        }
    }

}
 int SystemManager::getConfigFromUI()
 {
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

    _core->_config._enableHotPlug = (ui->chkEnableHotPlug->checkState() == Qt::CheckState::Checked)?true:false;
     return 0;
 }

void SystemManager::on_btnOk_clicked()
{
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

    int tOrigPluginIndex = -1;
    for(int i=0; i<ui->tableOrigPluginsSort->rowCount(); i++)
    {
        if(ui->tableOrigPluginsSort->item(i, 1)->text()==origPluginID)
        {
            tOrigPluginIndex = i;
            break;
        }
    }

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
    info._type = INFT_PLUGIN_COLLECT;
    emit PluginIO::getInstance()->sig_OutputInfo(info);
}
