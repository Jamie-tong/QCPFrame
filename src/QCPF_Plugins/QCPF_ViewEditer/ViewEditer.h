/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef FORMCONFIG_H
#define FORMCONFIG_H

#include <QDialog>
#include <QTreeWidget>
#include "PluginIO.h"
#include "../../QCPF_ViewModel/qcpf_viewmodel.h"
#include "../../QCPF_ViewModel/viewconfigmodel.h"
#include <QTreeWidget>
#include <QTableWidget>

namespace Ui {
class ViewEditer;
}

class ViewEditer : public QDialog
{
    Q_OBJECT

public:
    ViewEditer(QCPF_ViewModel* view, QWidget *parent = nullptr);
    ~ViewEditer();
    static ViewEditer* getInstance();//静态获取实例

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

signals:
    void sig_SelAllOrNot(bool flag);//for 全选/不选复选框
private slots:
    void slot_OnULoaded();
    void on_btnOk_clicked();
     int getConfigFromUI();
     int setConfigToUI();
     void on_btnCancel_clicked();

     void on_btnApply_clicked();

     void on_btnAddNode_clicked();
     void on_btnDeleteNode_clicked();

     void on_btnUp_clicked();
     void on_btnDown_clicked();
     void on_btnLeft_clicked();
     void on_btnRight_clicked();

     void on_btnAddAction_clicked();
     void on_btnAddSeperator_clicked();


     void on_treeMenuEdit_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

     void on_btnClearAction_clicked();

     void on_btnIconFinder_clicked();

     void on_btnAddAction_Toolbar_clicked();

     void on_btnAddSeperator_Toolbar_clicked();

     void on_btnAddWidget_Toolbar_clicked();

     void on_btnDeleteItem_Toolbar_clicked();

     void on_btnMoveUp_Toolbar_clicked();

     void on_btnMoveDown_Toolbar_clicked();

     void on_btnAddWidget_Statusbar_clicked();

     void on_btnDeleteItem_Statusbar_clicked();

     void on_btnMoveUp_Statusbar_clicked();

     void on_btnMoveDown_Statusbar_clicked();

     void on_btnAddToolbar_clicked();

     void on_btnDeleteToolbar_clicked();

     void TableItemMoveUp(QTableWidget *table);
     void TableItemMoveDown(QTableWidget *table);

     void TreeItemMoveUp(QTreeWidget* treeWidget);
     void TreeItemMoveDown(QTreeWidget* treeWidget);
     void TreeItemMoveLeft(QTreeWidget* treeWidget);
     void TreeItemMoveRight(QTreeWidget* treeWidget);

public slots:
    void treeWidgetOpenEditor(QTreeWidgetItem *item,int col);
    void slot_SelAllOrNot(bool flag);

public:
     QCPF_ViewModel *_view;

private:
    Ui::ViewEditer *ui;
    bool _isFirstResize = true;
    QTimer* _timer;
    int previousColNo = -1;
    tagOutputInfo tOutInfo;
    void setTableStyle(QTableWidget *table);
};

#endif // FORMCONFIG_H
