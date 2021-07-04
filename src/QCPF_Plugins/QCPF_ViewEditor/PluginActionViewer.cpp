/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "PluginActionViewer.h"
#include "ui_PluginActionViewer.h"
#include <QTimer>
#include <QStringLiteral>
#include <QMessageBox>

PluginActionViewer::PluginActionViewer(QCPF_Interface* model, QTreeWidgetItem* item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginActionViewer)
{
    ui->setupUi(this);

    _core = model;
    _selTreeItem = item;
    this->setParent(parent);


    setWindowFlags(Qt::Dialog
                   | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);


    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(362, 440));
    setMaximumSize(QSize(362, 440));
    setSizeGripEnabled(false);

    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnULoaded()));

    ui->buttonBox->setFocus();
    this->setWindowIcon(parent->windowIcon());
}

PluginActionViewer::~PluginActionViewer()
{
    delete ui;
}

void PluginActionViewer::showEvent(QShowEvent *event)
{
    _timer->start(1);
}

void PluginActionViewer::slot_OnULoaded()
{
    _isOk = false;
    ui->tabWidget->setCurrentIndex(0);
    on_tabWidget_currentChanged(0);
}

void PluginActionViewer::on_tabWidget_currentChanged(int index)
{
    ui->cbPluginID->clear();
    ui->txtActionName->clear();
    ui->txtActionDetail->clear();

    ui->cbCopyID->clear();
    if(index==0)
    {
        foreach(Plugin_Interface* pi,  _core->I_SysPlugins_Sel)
        {
            ui->cbPluginID->addItem(pi->I_PluginID);
        }
    }
    else
    {
        foreach(Plugin_Interface* pi,  _core->I_NSysOrigPlugins_Sel)
        {
            ui->cbPluginID->addItem(pi->I_PluginID);
        }
    }
}

void PluginActionViewer::on_cbPluginID_currentIndexChanged(int index)
{
    ui->cbPluginAction->clear();
    ui->txtActionName->clear();
    ui->txtActionDetail->clear();

    int tabIndex = ui->tabWidget->currentIndex();

    if(index<0)
        return;

    ui->cbCopyID->clear();
    if(tabIndex==0)
    {

        if(index >=_core->I_SysPlugins.count())
            return;

        foreach (PluginActionInfo* pai, _core->I_SysPlugins_Sel[index]->I_ActionList) {
            ui->cbPluginAction->addItem(pai->_actionName);
        }
    }
    else
    {
        if(index >=_core->I_NSysOrigPlugins_Sel.count())
            return;

        foreach (PluginActionInfo* pai, _core->I_NSysOrigPlugins_Sel[index]->I_ActionList) {
            ui->cbPluginAction->addItem(pai->_actionName);
        }
        ui->cbCopyID->addItem(tr("None"));
        foreach (Plugin_Interface* pai, _core->I_NSysClonePlugins) {
            if(pai->I_PluginID==ui->cbPluginID->currentText())
                ui->cbCopyID->addItem(pai->I_CopyID);
        }
    }
}

void PluginActionViewer::on_cbPluginAction_currentIndexChanged(int index)
{
    ui->txtActionName->clear();
    ui->txtActionDetail->clear();

    if(index<0)
        return;

    int tabIndex = ui->tabWidget->currentIndex();
    int plugIndex = ui->cbPluginID->currentIndex();
    if(tabIndex==0)
    {
        if(plugIndex >=_core->I_SysPlugins_Sel.count() || index >= _core->I_SysPlugins_Sel[plugIndex]->I_ActionList.count())
            return;

        ui->txtActionName->setText(_core->I_SysPlugins_Sel[plugIndex]->I_ActionList[index]->_actionName);
        ui->txtActionDetail->setText(_core->I_SysPlugins_Sel[plugIndex]->I_ActionList[index]->_actionDetail);
    }
    else
    {
        if(plugIndex >=_core->I_NSysOrigPlugins_Sel.count() || index >= _core->I_NSysOrigPlugins_Sel[plugIndex]->I_ActionList.count())
            return;

        ui->txtActionName->setText(_core->I_NSysOrigPlugins_Sel[plugIndex]->I_ActionList[index]->_actionName);
        ui->txtActionDetail->setText(_core->I_NSysOrigPlugins_Sel[plugIndex]->I_ActionList[index]->_actionDetail);
    }
}

void PluginActionViewer::on_buttonBox_accepted()
{
    _isOk = true;
    if(ui->tabWidget->currentIndex()==PT_SYS)
        _pluginType = tr("System");
    else
        _pluginType = tr("Non-System");

    _pluginID = ui->cbPluginID->currentText();
    _copyID = ui->cbCopyID->currentText();
    _actionName = ui->txtActionName->text();
    _actionDetail = ui->txtActionDetail->toPlainText();
}
