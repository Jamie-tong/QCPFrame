/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef PLUGINWIDGETVIEWER_H
#define PLUGINWIDGETVIEWER_H

#include <QDialog>
#include "../../QCPF_Model/qcpf_model.h"
#include <QTableWidget>

namespace Ui {
class PluginWidgetViewer;
}

class PluginWidgetViewer : public QDialog
{
    Q_OBJECT

public:
    explicit PluginWidgetViewer(QCPF_Interface* model, bool isShowStatusBarItemType, QWidget *parent = nullptr);
    ~PluginWidgetViewer();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void slot_OnULoaded();

    void on_tabWidget_currentChanged(int index);

    void on_cbPluginID_currentIndexChanged(int index);

    void on_cbPluginWidget_currentIndexChanged(int index);

    void on_buttonBox_accepted();


public:
    bool _isOk;
    int _pluginType;
    QString _pluginID;
    QString _copyID;
    QString _widgetObjectName;
    int _statusbarItemType;//StatusbarItemType

    QString _itemTag;
    QString _itemDetail;

    int _widgetOrigWidth;
    int _widgetOrigHeight;
private:
    Ui::PluginWidgetViewer *ui;
    QTimer* _timer;
    QCPF_Interface* _core;
    bool _isShowAlignment;
};

#endif // PLUGINWIDGETVIEWER_H
