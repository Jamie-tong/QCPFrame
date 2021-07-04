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
#include "../../QCPF_Model/qcpf_model.h"

namespace Ui {
class SystemManager;
}

class SystemManager : public QDialog
{
    Q_OBJECT

public:
    SystemManager(QCPF_Model* model, QWidget *parent = nullptr);
    ~SystemManager();
    static SystemManager* getInstance();

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

    void on_btnOrigPluginMoveUp_clicked();

    void on_btnOrigPluginMoveDown_clicked();

    void on_btnUpdate_clicked();

private:
    Ui::SystemManager *ui;
    QCPF_Model *_core;
    bool _isFirstResize = true;
    QTimer* _timer;
};

#endif // FORMCONFIG_H
