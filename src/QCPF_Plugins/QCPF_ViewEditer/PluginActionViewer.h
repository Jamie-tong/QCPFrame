/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef PLUGINCONNECTOR_H
#define PLUGINCONNECTOR_H

#include <QDialog>
#include "PluginIO.h"
#include "../../QCPF_Model/qcpf_model.h"
#include <QTreeWidget>

namespace Ui {
class PluginActionViewer;
}

class PluginActionViewer : public QDialog
{
    Q_OBJECT

public:
    explicit PluginActionViewer(QCPF_Interface* model, QTreeWidgetItem* item, QWidget *parent);
    ~PluginActionViewer();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void slot_OnULoaded();

    void on_tabWidget_currentChanged(int index);

    void on_cbPluginID_currentIndexChanged(int index);

    void on_cbPluginAction_currentIndexChanged(int index);

    void on_buttonBox_accepted();

public:
    bool _isOk;
    QString _pluginType;
    QString _pluginID;
    QString _copyID;
    QString _actionName;
    QString _actionDetail;
private:
    Ui::PluginActionViewer *ui;
    QTimer* _timer;
    QCPF_Interface* _core;
    QTreeWidgetItem* _selTreeItem;
};

#endif // PLUGINCONNECTOR_H
