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
class ViewEditor;
}

class ViewEditor : public QDialog
{
    Q_OBJECT

public:
    ViewEditor(QWidget *parent = nullptr);
    ~ViewEditor();
    static ViewEditor* getInstance();//静态获取实例

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

     void on_btnAddNode_clicked();
     void on_btnDeleteNode_clicked();

     void on_btnUp_clicked();
     void on_btnDown_clicked();
     void on_btnLeft_clicked();
     void on_btnRight_clicked();


     void on_treeMenuEdit_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

     void on_btnClearAction_clicked();

     void on_btnIconFinder_clicked();

     void on_btnAddAction_Toolbar_clicked();

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

     void on_btnLoadAction_clicked();

     void on_tablePluginWidget_itemClicked(QTableWidgetItem *item);

     void on_btnAddSpacer_Toolbar_clicked();

     void on_btnAddSeparator_Toolbar_clicked();

     void on_btnAddSeparator_clicked();


     void on_treeMenuEdit_itemDoubleClicked(QTreeWidgetItem *item, int column);

     void on_treeToolbarEdit_itemDoubleClicked(QTreeWidgetItem *item, int column);

     void on_tableStatusbarEditer_itemDoubleClicked(QTableWidgetItem *item);

     void on_treeToolbarEdit_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

     void on_tableStatusbarEditer_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

public slots:
     void slot_SelAllOrNot(bool flag);
     void OnLineEdit_EditingFinished_Tree(void);
     void OnKeyEdit_EditingFinished_Tree(void);
     void OnComboBox_Activated_Index_Tree(int);
     void OnComboBox_Activated_Text_Tree(int);
     void OnSpinBox_ValueChanged_Tree(int);

     void OnComboBox_Activated_Text_Table(int);

public:
     PluginIO* pluginInst;
     QCPF_ViewModel *_view;

private:
    Ui::ViewEditor *ui;
    bool _isFirstResize = true;
    QTimer* _timer;
    int previousColNo = -1;
    tagOutputInfo tOutInfo;
    void setTableStyle(QTableWidget *table);
    QString getPluginWidgetTag(int rowIndex);

    QTreeWidget* _currentTree;
    QTreeWidgetItem* _currentItem_TreeMenuEdit;
    int _currentCol_TreeMenuEdit;

    QTableWidget* _currentTable;
    QTableWidgetItem* _currentItem_tableStatusbarEditer;
};

#endif // FORMCONFIG_H
