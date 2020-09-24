/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "pluginwidgetviewer.h"
#include "ui_pluginwidgetviewer.h"
#include <QTimer>
#include <QStringLiteral>
#include <QMessageBox>

PluginWidgetViewer::PluginWidgetViewer(QCPF_Interface* model, bool isShowStatusBarItemType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginWidgetViewer)
{
    ui->setupUi(this);

    _core = model;
    this->setParent(parent);

    //去掉问号按钮
    setWindowFlags(Qt::Dialog
                   | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    //禁止调整大小
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(360, 456));
    setMaximumSize(QSize(360, 456));
    setSizeGripEnabled(false);

    _isShowAlignment = isShowStatusBarItemType;
    ui->cbStatusbarItemType->setEnabled(isShowStatusBarItemType);
    //注册面板显示后的信号槽
    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnULoaded()));
}

PluginWidgetViewer::~PluginWidgetViewer()
{
    delete ui;
}

void PluginWidgetViewer::showEvent(QShowEvent *event)
{
    _timer->start(1);
}

void PluginWidgetViewer::slot_OnULoaded()
{
    _isOk = false;
    ui->tabWidget->setCurrentIndex(0);
    on_tabWidget_currentChanged(0);
}

void PluginWidgetViewer::on_tabWidget_currentChanged(int index)
{
    ui->cbPluginID->clear();
    ui->txtWidgetObjectName->clear();
    ui->txtWidgetDetail->clear();

    ui->cbCopyID->clear();
    ui->cbCopyID->addItem("None");
    if(index==0)//系统组件
    {
        foreach(Plugin_Interface* pi,  _core->I_SysPlugins_Sel)
        {
            ui->cbPluginID->addItem(pi->I_PluginID);
        }
    }
    else//非系统组件
    {
        foreach(Plugin_Interface* pi,  _core->I_NSysOrigPlugins_Sel)
        {
            ui->cbPluginID->addItem(pi->I_PluginID);
        }
    }
}

void PluginWidgetViewer::on_cbPluginID_currentIndexChanged(int index)
{
    ui->cbPluginWidget->clear();
    ui->txtWidgetObjectName->clear();
    ui->txtWidgetDetail->clear();

    int tabIndex = ui->tabWidget->currentIndex();

    if(index<0)
        return;

    ui->cbCopyID->clear();
    ui->cbCopyID->addItem("None");
    if(tabIndex==0)//系统组件
    {

        if(index >=_core->I_SysPlugins.count())
            return;

        foreach (PluginWidgetInfo* pai, _core->I_SysPlugins_Sel[index]->I_WidgetList) {
            ui->cbPluginWidget->addItem(pai->_widget->objectName());
        }
    }
    else//非系统组件
    {
        if(index >=_core->I_NSysOrigPlugins_Sel.count())
            return;

        foreach (PluginWidgetInfo* pai, _core->I_NSysOrigPlugins_Sel[index]->I_WidgetList) {
            ui->cbPluginWidget->addItem(pai->_widget->objectName());
        }
        foreach (Plugin_Interface* pai, _core->I_NSysClonePlugins) {
            if(pai->I_PluginID==ui->cbPluginID->currentText())
                ui->cbCopyID->addItem(pai->I_CopyID);
        }
    }
}

void PluginWidgetViewer::on_cbPluginWidget_currentIndexChanged(int index)
{
    ui->txtWidgetObjectName->clear();
    ui->txtWidgetDetail->clear();

    if(index<0)
        return;

    int tabIndex = ui->tabWidget->currentIndex();
    int plugIndex = ui->cbPluginID->currentIndex();
    if(tabIndex==PT_SYS)//系统组件
    {
        if(plugIndex >=_core->I_SysPlugins_Sel.count() || index >= _core->I_SysPlugins_Sel[plugIndex]->I_WidgetList.count())
            return;

        ui->txtWidgetObjectName->setText(_core->I_SysPlugins_Sel[plugIndex]->I_WidgetList[index]->_widget->objectName());
        _widgetOrigWidth = _core->I_SysPlugins_Sel[plugIndex]->I_WidgetList[index]->_widget->width();
        _widgetOrigHeight = _core->I_SysPlugins_Sel[plugIndex]->I_WidgetList[index]->_widget->height();
        ui->txtWidgetOrigSize->setText(QString("%1 x %2").arg(_widgetOrigWidth).arg(_widgetOrigHeight));
        ui->txtWidgetDetail->setText(_core->I_SysPlugins_Sel[plugIndex]->I_WidgetList[index]->_widgetDetail);
    }
    else//非系统组件
    {
        if(plugIndex >=_core->I_NSysOrigPlugins_Sel.count() || index >= _core->I_NSysOrigPlugins_Sel[plugIndex]->I_WidgetList.count())
            return;

        ui->txtWidgetObjectName->setText(_core->I_NSysOrigPlugins_Sel[plugIndex]->I_WidgetList[index]->_widget->objectName());
        _widgetOrigWidth = _core->I_NSysOrigPlugins_Sel[plugIndex]->I_WidgetList[index]->_widget->width();
        _widgetOrigHeight = _core->I_NSysOrigPlugins_Sel[plugIndex]->I_WidgetList[index]->_widget->height();
        ui->txtWidgetOrigSize->setText(QString("%1 x %2").arg(_widgetOrigWidth).arg(_widgetOrigHeight));
        ui->txtWidgetDetail->setText(_core->I_NSysOrigPlugins_Sel[plugIndex]->I_WidgetList[index]->_widgetDetail);
    }
}

void PluginWidgetViewer::on_buttonBox_accepted()
{
    _isOk = true;

    _pluginType = ui->tabWidget->currentIndex();
    _pluginID = ui->cbPluginID->currentText();
    _statusbarItemType = ui->cbStatusbarItemType->currentIndex();

    if(ui->cbCopyID->currentText() == "None")
        _copyID = "";
    else
         _copyID = ui->cbCopyID->currentText();

    _widgetObjectName = ui->txtWidgetObjectName->text();

    QString pluginType = _pluginType==PT_SYS?tr("System"):tr("NonSystem");

    _itemTag = _widgetObjectName + ";" + pluginType + ";" +_pluginID + ";" + _copyID;

    _itemDetail = ui->txtWidgetDetail->toPlainText();
}

