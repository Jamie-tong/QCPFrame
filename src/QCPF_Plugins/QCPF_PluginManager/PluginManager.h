/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef FORMCONFIG_H
#define FORMCONFIG_H

#include <QDialog>

#include <QTreeWidgetItem>
#include <QTableWidget>
#include "qcpf_model.h"

namespace Ui {
class PluginManager;
}

class PluginManager : public QDialog
{
    Q_OBJECT

public:
    PluginManager(QCPF_Model* model, QWidget *parent = nullptr);
    ~PluginManager();
    static PluginManager* getInstance();

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
private:
    int getConfigFromUI();
    void setTableStyle(QTableWidget *table);

public:
     int setConfigToUI();

signals:
    int sig_Save();
    int sig_Cancel();
    int sig_Apply();

    void sig_SelAllOrNot(bool flag);

private slots:
    void slot_OnULoaded();
    void slot_SelAllOrNot(bool flag);

    void on_btnOk_clicked();
    void on_btnCancel_clicked();

    void on_pluginCheckbox_selChanged(int state);

    void on_cbOriginPluginLst_currentIndexChanged(int index);

    void on_btnClone_clicked();
    void on_btnDeleteClone_clicked();

    void on_treePluginClone_itemPressed(QTreeWidgetItem *item, int column);

    void on_btnOrigPluginMoveUp_clicked();
    void on_btnOrigPluginMoveDown_clicked();
    void on_btnValidPluginMoveUp_clicked();
    void on_btnValidPluginMoveDown_clicked();


    void on_btnRefreshPlugins_clicked();

private:
    Ui::PluginManager *ui;
    QCPF_Model *_core;
    bool _isFirstResize = true;
    QTimer* _timer;
};

#endif // FORMCONFIG_H
