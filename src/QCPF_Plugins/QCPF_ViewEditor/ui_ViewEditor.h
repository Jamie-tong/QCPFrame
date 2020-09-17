/********************************************************************************
** Form generated from reading UI file 'ViewEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWEDITOR_H
#define UI_VIEWEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QKeySequenceEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewEditor
{
public:
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QPushButton *btnApply;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QPushButton *btnAddNode;
    QLabel *label_2;
    QLabel *label_8;
    QLineEdit *txtMenuTitle;
    QKeySequenceEdit *txtMenuShortcut;
    QPushButton *btnDeleteNode;
    QPushButton *btnAddSeperator;
    QCheckBox *chkMenuCheckable;
    QComboBox *cbMenuAuthority;
    QLabel *label;
    QGroupBox *groupBox_2;
    QFrame *frame_2;
    QPushButton *btnUp;
    QPushButton *btnLeft;
    QPushButton *btnDown;
    QPushButton *btnRight;
    QFrame *frame_5;
    QPushButton *btnIconFinder;
    QFrame *frame_3;
    QPushButton *btnLoadAction;
    QPushButton *btnClearAction;
    QTreeWidget *treeMenuEdit;
    QWidget *tab_3;
    QGroupBox *groupBox_3;
    QFrame *frame_8;
    QComboBox *cbActionFromMenu_Toolbar;
    QLabel *label_3;
    QFrame *frame_7;
    QPushButton *btnAddAction_Toolbar;
    QPushButton *btnAddSeperator_Toolbar;
    QPushButton *btnDeleteItem_Toolbar;
    QPushButton *btnAddWidget_Toolbar;
    QFrame *frame_9;
    QSpinBox *spanToolbarHight;
    QLabel *label_4;
    QFrame *frame_10;
    QSpinBox *spanItemHeight_Toolbar;
    QSpinBox *spanItemWidth_Toolbar;
    QLabel *label_5;
    QLabel *label_6;
    QFrame *frame_15;
    QPushButton *btnMoveDown_Toolbar;
    QPushButton *btnMoveUp_Toolbar;
    QTreeWidget *treeToolbarEdit;
    QFrame *frame_11;
    QPushButton *btnAddToolbar;
    QGroupBox *groupBox_4;
    QFrame *frame_12;
    QPushButton *btnDeleteItem_Statusbar;
    QPushButton *btnAddWidget_Statusbar;
    QFrame *frame_13;
    QSpinBox *spanStatusbarHeight;
    QLabel *label_9;
    QFrame *frame_14;
    QSpinBox *spanItemHeight_Statusbar;
    QSpinBox *spanItemWidth_Statusbar;
    QLabel *label_10;
    QLabel *label_11;
    QTableWidget *tableStatusbarEditer;
    QFrame *frame_16;
    QPushButton *btnMoveDown_Statusbar;
    QPushButton *btnMoveUp_Statusbar;
    QWidget *tab_5;
    QTableWidget *tablePluginWidget;
    QWidget *tab_2;
    QCheckBox *chb_IsShowStatusBar;
    QCheckBox *chb_IsShowMenu;
    QCheckBox *chb_IsShowToolBar;
    QGroupBox *groupBox;

    void setupUi(QDialog *ViewEditor)
    {
        if (ViewEditor->objectName().isEmpty())
            ViewEditor->setObjectName(QString::fromUtf8("ViewEditor"));
        ViewEditor->resize(1207, 780);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../bin/debug/Images/viewedit.png"), QSize(), QIcon::Normal, QIcon::Off);
        ViewEditor->setWindowIcon(icon);
        ViewEditor->setAutoFillBackground(true);
        btnOk = new QPushButton(ViewEditor);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(843, 730, 100, 35));
        btnOk->setMinimumSize(QSize(0, 35));
        btnCancel = new QPushButton(ViewEditor);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(1100, 730, 100, 35));
        btnCancel->setMinimumSize(QSize(0, 35));
        btnApply = new QPushButton(ViewEditor);
        btnApply->setObjectName(QString::fromUtf8("btnApply"));
        btnApply->setGeometry(QRect(946, 730, 100, 35));
        btnApply->setMinimumSize(QSize(0, 35));
        tabWidget = new QTabWidget(ViewEditor);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(8, 0, 1200, 720));
        tabWidget->setAutoFillBackground(true);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabWidget->setDocumentMode(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(1030, 10, 163, 679));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(verticalLayoutWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("border-color: qlineargradient(spread:pad, x1:1, y1:0.534, x2:1, y2:0, stop:0 rgba(185, 185, 185, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-color: rgb(159, 159, 159);"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        btnAddNode = new QPushButton(frame);
        btnAddNode->setObjectName(QString::fromUtf8("btnAddNode"));
        btnAddNode->setGeometry(QRect(10, 218, 141, 41));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 141, 16));
        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 60, 141, 16));
        txtMenuTitle = new QLineEdit(frame);
        txtMenuTitle->setObjectName(QString::fromUtf8("txtMenuTitle"));
        txtMenuTitle->setGeometry(QRect(10, 30, 141, 20));
        txtMenuShortcut = new QKeySequenceEdit(frame);
        txtMenuShortcut->setObjectName(QString::fromUtf8("txtMenuShortcut"));
        txtMenuShortcut->setGeometry(QRect(10, 80, 141, 20));
        btnDeleteNode = new QPushButton(frame);
        btnDeleteNode->setObjectName(QString::fromUtf8("btnDeleteNode"));
        btnDeleteNode->setEnabled(true);
        btnDeleteNode->setGeometry(QRect(10, 320, 141, 41));
        btnAddSeperator = new QPushButton(frame);
        btnAddSeperator->setObjectName(QString::fromUtf8("btnAddSeperator"));
        btnAddSeperator->setGeometry(QRect(10, 260, 141, 41));
        chkMenuCheckable = new QCheckBox(frame);
        chkMenuCheckable->setObjectName(QString::fromUtf8("chkMenuCheckable"));
        chkMenuCheckable->setGeometry(QRect(10, 180, 141, 16));
        cbMenuAuthority = new QComboBox(frame);
        cbMenuAuthority->addItem(QString());
        cbMenuAuthority->addItem(QString());
        cbMenuAuthority->addItem(QString());
        cbMenuAuthority->addItem(QString());
        cbMenuAuthority->addItem(QString());
        cbMenuAuthority->addItem(QString());
        cbMenuAuthority->addItem(QString());
        cbMenuAuthority->addItem(QString());
        cbMenuAuthority->addItem(QString());
        cbMenuAuthority->addItem(QString());
        cbMenuAuthority->setObjectName(QString::fromUtf8("cbMenuAuthority"));
        cbMenuAuthority->setGeometry(QRect(10, 138, 141, 22));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 113, 71, 16));
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(-8, 206, 200, 3));

        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(verticalLayoutWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Sunken);
        btnUp = new QPushButton(frame_2);
        btnUp->setObjectName(QString::fromUtf8("btnUp"));
        btnUp->setGeometry(QRect(60, 10, 41, 31));
        btnLeft = new QPushButton(frame_2);
        btnLeft->setObjectName(QString::fromUtf8("btnLeft"));
        btnLeft->setGeometry(QRect(10, 50, 41, 31));
        btnDown = new QPushButton(frame_2);
        btnDown->setObjectName(QString::fromUtf8("btnDown"));
        btnDown->setGeometry(QRect(60, 50, 41, 31));
        btnRight = new QPushButton(frame_2);
        btnRight->setObjectName(QString::fromUtf8("btnRight"));
        btnRight->setGeometry(QRect(110, 50, 41, 31));

        verticalLayout->addWidget(frame_2);

        frame_5 = new QFrame(verticalLayoutWidget);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::Box);
        frame_5->setFrameShadow(QFrame::Sunken);
        btnIconFinder = new QPushButton(frame_5);
        btnIconFinder->setObjectName(QString::fromUtf8("btnIconFinder"));
        btnIconFinder->setGeometry(QRect(10, 15, 141, 41));

        verticalLayout->addWidget(frame_5);

        frame_3 = new QFrame(verticalLayoutWidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::Box);
        frame_3->setFrameShadow(QFrame::Sunken);
        btnLoadAction = new QPushButton(frame_3);
        btnLoadAction->setObjectName(QString::fromUtf8("btnLoadAction"));
        btnLoadAction->setGeometry(QRect(10, 15, 141, 41));
        btnClearAction = new QPushButton(frame_3);
        btnClearAction->setObjectName(QString::fromUtf8("btnClearAction"));
        btnClearAction->setGeometry(QRect(10, 65, 141, 41));

        verticalLayout->addWidget(frame_3);

        verticalLayout->setStretch(0, 65);
        verticalLayout->setStretch(1, 16);
        verticalLayout->setStretch(2, 12);
        verticalLayout->setStretch(3, 20);
        treeMenuEdit = new QTreeWidget(tab);
        treeMenuEdit->setObjectName(QString::fromUtf8("treeMenuEdit"));
        treeMenuEdit->setGeometry(QRect(0, 10, 1021, 679));
        treeMenuEdit->setMidLineWidth(0);
        treeMenuEdit->setProperty("showDropIndicator", QVariant(true));
        treeMenuEdit->setAlternatingRowColors(true);
        treeMenuEdit->setHeaderHidden(true);
        treeMenuEdit->header()->setVisible(false);
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 4, 591, 688));
        frame_8 = new QFrame(groupBox_3);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setGeometry(QRect(420, 82, 161, 61));
        frame_8->setFrameShape(QFrame::Box);
        frame_8->setFrameShadow(QFrame::Sunken);
        cbActionFromMenu_Toolbar = new QComboBox(frame_8);
        cbActionFromMenu_Toolbar->setObjectName(QString::fromUtf8("cbActionFromMenu_Toolbar"));
        cbActionFromMenu_Toolbar->setGeometry(QRect(10, 30, 141, 22));
        label_3 = new QLabel(frame_8);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 111, 16));
        frame_7 = new QFrame(groupBox_3);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setGeometry(QRect(420, 266, 161, 221));
        frame_7->setFrameShape(QFrame::Box);
        frame_7->setFrameShadow(QFrame::Sunken);
        btnAddAction_Toolbar = new QPushButton(frame_7);
        btnAddAction_Toolbar->setObjectName(QString::fromUtf8("btnAddAction_Toolbar"));
        btnAddAction_Toolbar->setGeometry(QRect(10, 9, 141, 41));
        btnAddSeperator_Toolbar = new QPushButton(frame_7);
        btnAddSeperator_Toolbar->setObjectName(QString::fromUtf8("btnAddSeperator_Toolbar"));
        btnAddSeperator_Toolbar->setGeometry(QRect(10, 55, 141, 41));
        btnDeleteItem_Toolbar = new QPushButton(frame_7);
        btnDeleteItem_Toolbar->setObjectName(QString::fromUtf8("btnDeleteItem_Toolbar"));
        btnDeleteItem_Toolbar->setGeometry(QRect(10, 170, 141, 41));
        btnAddWidget_Toolbar = new QPushButton(frame_7);
        btnAddWidget_Toolbar->setObjectName(QString::fromUtf8("btnAddWidget_Toolbar"));
        btnAddWidget_Toolbar->setGeometry(QRect(10, 101, 141, 41));
        frame_9 = new QFrame(groupBox_3);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        frame_9->setGeometry(QRect(420, 616, 161, 61));
        frame_9->setFrameShape(QFrame::Box);
        frame_9->setFrameShadow(QFrame::Sunken);
        spanToolbarHight = new QSpinBox(frame_9);
        spanToolbarHight->setObjectName(QString::fromUtf8("spanToolbarHight"));
        spanToolbarHight->setGeometry(QRect(10, 30, 141, 22));
        spanToolbarHight->setMinimum(16);
        spanToolbarHight->setMaximum(128);
        spanToolbarHight->setValue(32);
        label_4 = new QLabel(frame_9);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 10, 101, 16));
        frame_10 = new QFrame(groupBox_3);
        frame_10->setObjectName(QString::fromUtf8("frame_10"));
        frame_10->setGeometry(QRect(420, 149, 161, 111));
        frame_10->setFrameShape(QFrame::Box);
        frame_10->setFrameShadow(QFrame::Sunken);
        spanItemHeight_Toolbar = new QSpinBox(frame_10);
        spanItemHeight_Toolbar->setObjectName(QString::fromUtf8("spanItemHeight_Toolbar"));
        spanItemHeight_Toolbar->setGeometry(QRect(10, 75, 141, 22));
        spanItemHeight_Toolbar->setMinimum(16);
        spanItemHeight_Toolbar->setMaximum(128);
        spanItemHeight_Toolbar->setValue(32);
        spanItemWidth_Toolbar = new QSpinBox(frame_10);
        spanItemWidth_Toolbar->setObjectName(QString::fromUtf8("spanItemWidth_Toolbar"));
        spanItemWidth_Toolbar->setGeometry(QRect(10, 25, 141, 22));
        spanItemWidth_Toolbar->setMinimum(16);
        spanItemWidth_Toolbar->setMaximum(128);
        spanItemWidth_Toolbar->setValue(32);
        label_5 = new QLabel(frame_10);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 5, 101, 16));
        label_6 = new QLabel(frame_10);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 55, 101, 16));
        frame_15 = new QFrame(groupBox_3);
        frame_15->setObjectName(QString::fromUtf8("frame_15"));
        frame_15->setGeometry(QRect(420, 493, 161, 111));
        frame_15->setFrameShape(QFrame::Box);
        frame_15->setFrameShadow(QFrame::Sunken);
        btnMoveDown_Toolbar = new QPushButton(frame_15);
        btnMoveDown_Toolbar->setObjectName(QString::fromUtf8("btnMoveDown_Toolbar"));
        btnMoveDown_Toolbar->setGeometry(QRect(10, 60, 141, 41));
        btnMoveUp_Toolbar = new QPushButton(frame_15);
        btnMoveUp_Toolbar->setObjectName(QString::fromUtf8("btnMoveUp_Toolbar"));
        btnMoveUp_Toolbar->setGeometry(QRect(10, 10, 141, 41));
        treeToolbarEdit = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeToolbarEdit->setHeaderItem(__qtreewidgetitem);
        treeToolbarEdit->setObjectName(QString::fromUtf8("treeToolbarEdit"));
        treeToolbarEdit->setGeometry(QRect(10, 15, 401, 661));
        treeToolbarEdit->setMidLineWidth(0);
        treeToolbarEdit->setProperty("showDropIndicator", QVariant(true));
        treeToolbarEdit->setAlternatingRowColors(true);
        treeToolbarEdit->setHeaderHidden(true);
        treeToolbarEdit->header()->setVisible(false);
        frame_11 = new QFrame(groupBox_3);
        frame_11->setObjectName(QString::fromUtf8("frame_11"));
        frame_11->setGeometry(QRect(420, 15, 161, 61));
        frame_11->setFrameShape(QFrame::Box);
        frame_11->setFrameShadow(QFrame::Sunken);
        btnAddToolbar = new QPushButton(frame_11);
        btnAddToolbar->setObjectName(QString::fromUtf8("btnAddToolbar"));
        btnAddToolbar->setGeometry(QRect(10, 10, 141, 41));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(600, 4, 591, 688));
        frame_12 = new QFrame(groupBox_4);
        frame_12->setObjectName(QString::fromUtf8("frame_12"));
        frame_12->setGeometry(QRect(420, 147, 161, 131));
        frame_12->setFrameShape(QFrame::Box);
        frame_12->setFrameShadow(QFrame::Sunken);
        btnDeleteItem_Statusbar = new QPushButton(frame_12);
        btnDeleteItem_Statusbar->setObjectName(QString::fromUtf8("btnDeleteItem_Statusbar"));
        btnDeleteItem_Statusbar->setGeometry(QRect(10, 80, 141, 41));
        btnAddWidget_Statusbar = new QPushButton(frame_12);
        btnAddWidget_Statusbar->setObjectName(QString::fromUtf8("btnAddWidget_Statusbar"));
        btnAddWidget_Statusbar->setGeometry(QRect(10, 10, 141, 41));
        frame_13 = new QFrame(groupBox_4);
        frame_13->setObjectName(QString::fromUtf8("frame_13"));
        frame_13->setGeometry(QRect(420, 606, 161, 71));
        frame_13->setFrameShape(QFrame::Box);
        frame_13->setFrameShadow(QFrame::Sunken);
        spanStatusbarHeight = new QSpinBox(frame_13);
        spanStatusbarHeight->setObjectName(QString::fromUtf8("spanStatusbarHeight"));
        spanStatusbarHeight->setGeometry(QRect(10, 30, 141, 22));
        label_9 = new QLabel(frame_13);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 10, 101, 16));
        frame_14 = new QFrame(groupBox_4);
        frame_14->setObjectName(QString::fromUtf8("frame_14"));
        frame_14->setGeometry(QRect(420, 16, 161, 121));
        frame_14->setFrameShape(QFrame::Box);
        frame_14->setFrameShadow(QFrame::Sunken);
        spanItemHeight_Statusbar = new QSpinBox(frame_14);
        spanItemHeight_Statusbar->setObjectName(QString::fromUtf8("spanItemHeight_Statusbar"));
        spanItemHeight_Statusbar->setGeometry(QRect(10, 80, 141, 22));
        spanItemHeight_Statusbar->setMinimum(16);
        spanItemHeight_Statusbar->setMaximum(48);
        spanItemHeight_Statusbar->setValue(32);
        spanItemWidth_Statusbar = new QSpinBox(frame_14);
        spanItemWidth_Statusbar->setObjectName(QString::fromUtf8("spanItemWidth_Statusbar"));
        spanItemWidth_Statusbar->setGeometry(QRect(10, 30, 141, 22));
        spanItemWidth_Statusbar->setMinimum(16);
        spanItemWidth_Statusbar->setMaximum(48);
        spanItemWidth_Statusbar->setValue(32);
        label_10 = new QLabel(frame_14);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 10, 101, 16));
        label_11 = new QLabel(frame_14);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 60, 101, 16));
        tableStatusbarEditer = new QTableWidget(groupBox_4);
        if (tableStatusbarEditer->columnCount() < 4)
            tableStatusbarEditer->setColumnCount(4);
        if (tableStatusbarEditer->rowCount() < 40)
            tableStatusbarEditer->setRowCount(40);
        tableStatusbarEditer->setObjectName(QString::fromUtf8("tableStatusbarEditer"));
        tableStatusbarEditer->setGeometry(QRect(10, 16, 400, 660));
        tableStatusbarEditer->setMouseTracking(false);
        tableStatusbarEditer->setAutoFillBackground(false);
        tableStatusbarEditer->setStyleSheet(QString::fromUtf8(""));
        tableStatusbarEditer->setFrameShape(QFrame::StyledPanel);
        tableStatusbarEditer->setFrameShadow(QFrame::Plain);
        tableStatusbarEditer->setAutoScroll(true);
        tableStatusbarEditer->setProperty("showDropIndicator", QVariant(true));
        tableStatusbarEditer->setAlternatingRowColors(true);
        tableStatusbarEditer->setSelectionMode(QAbstractItemView::MultiSelection);
        tableStatusbarEditer->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableStatusbarEditer->setShowGrid(true);
        tableStatusbarEditer->setGridStyle(Qt::SolidLine);
        tableStatusbarEditer->setWordWrap(true);
        tableStatusbarEditer->setRowCount(40);
        tableStatusbarEditer->setColumnCount(4);
        tableStatusbarEditer->horizontalHeader()->setVisible(false);
        tableStatusbarEditer->horizontalHeader()->setCascadingSectionResizes(false);
        tableStatusbarEditer->horizontalHeader()->setDefaultSectionSize(60);
        tableStatusbarEditer->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableStatusbarEditer->horizontalHeader()->setStretchLastSection(true);
        tableStatusbarEditer->verticalHeader()->setVisible(false);
        tableStatusbarEditer->verticalHeader()->setCascadingSectionResizes(false);
        tableStatusbarEditer->verticalHeader()->setMinimumSectionSize(18);
        tableStatusbarEditer->verticalHeader()->setDefaultSectionSize(18);
        tableStatusbarEditer->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableStatusbarEditer->verticalHeader()->setStretchLastSection(false);
        frame_16 = new QFrame(groupBox_4);
        frame_16->setObjectName(QString::fromUtf8("frame_16"));
        frame_16->setGeometry(QRect(420, 286, 161, 111));
        frame_16->setFrameShape(QFrame::Box);
        frame_16->setFrameShadow(QFrame::Sunken);
        btnMoveDown_Statusbar = new QPushButton(frame_16);
        btnMoveDown_Statusbar->setObjectName(QString::fromUtf8("btnMoveDown_Statusbar"));
        btnMoveDown_Statusbar->setGeometry(QRect(10, 60, 141, 41));
        btnMoveUp_Statusbar = new QPushButton(frame_16);
        btnMoveUp_Statusbar->setObjectName(QString::fromUtf8("btnMoveUp_Statusbar"));
        btnMoveUp_Statusbar->setGeometry(QRect(10, 10, 141, 41));
        tabWidget->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        tablePluginWidget = new QTableWidget(tab_5);
        if (tablePluginWidget->columnCount() < 4)
            tablePluginWidget->setColumnCount(4);
        if (tablePluginWidget->rowCount() < 40)
            tablePluginWidget->setRowCount(40);
        tablePluginWidget->setObjectName(QString::fromUtf8("tablePluginWidget"));
        tablePluginWidget->setGeometry(QRect(0, 10, 1191, 681));
        tablePluginWidget->setMouseTracking(false);
        tablePluginWidget->setAutoFillBackground(false);
        tablePluginWidget->setStyleSheet(QString::fromUtf8(""));
        tablePluginWidget->setFrameShape(QFrame::StyledPanel);
        tablePluginWidget->setFrameShadow(QFrame::Plain);
        tablePluginWidget->setAutoScroll(true);
        tablePluginWidget->setProperty("showDropIndicator", QVariant(true));
        tablePluginWidget->setAlternatingRowColors(true);
        tablePluginWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        tablePluginWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tablePluginWidget->setShowGrid(true);
        tablePluginWidget->setGridStyle(Qt::SolidLine);
        tablePluginWidget->setWordWrap(true);
        tablePluginWidget->setRowCount(40);
        tablePluginWidget->setColumnCount(4);
        tablePluginWidget->horizontalHeader()->setVisible(false);
        tablePluginWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tablePluginWidget->horizontalHeader()->setDefaultSectionSize(60);
        tablePluginWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tablePluginWidget->horizontalHeader()->setStretchLastSection(true);
        tablePluginWidget->verticalHeader()->setVisible(false);
        tablePluginWidget->verticalHeader()->setCascadingSectionResizes(false);
        tablePluginWidget->verticalHeader()->setMinimumSectionSize(18);
        tablePluginWidget->verticalHeader()->setDefaultSectionSize(18);
        tablePluginWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tablePluginWidget->verticalHeader()->setStretchLastSection(false);
        tabWidget->addTab(tab_5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        chb_IsShowStatusBar = new QCheckBox(tab_2);
        chb_IsShowStatusBar->setObjectName(QString::fromUtf8("chb_IsShowStatusBar"));
        chb_IsShowStatusBar->setGeometry(QRect(30, 90, 111, 16));
        chb_IsShowMenu = new QCheckBox(tab_2);
        chb_IsShowMenu->setObjectName(QString::fromUtf8("chb_IsShowMenu"));
        chb_IsShowMenu->setGeometry(QRect(30, 30, 111, 16));
        chb_IsShowToolBar = new QCheckBox(tab_2);
        chb_IsShowToolBar->setObjectName(QString::fromUtf8("chb_IsShowToolBar"));
        chb_IsShowToolBar->setGeometry(QRect(30, 60, 111, 16));
        tabWidget->addTab(tab_2, QString());
        groupBox = new QGroupBox(ViewEditor);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(-10, 720, 1500, 2));
        groupBox->setFlat(true);

        retranslateUi(ViewEditor);

        tabWidget->setCurrentIndex(1);
        cbMenuAuthority->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(ViewEditor);
    } // setupUi

    void retranslateUi(QDialog *ViewEditor)
    {
        ViewEditor->setWindowTitle(QCoreApplication::translate("ViewEditor", "View Editor", nullptr));
        btnOk->setText(QCoreApplication::translate("ViewEditor", "Ok(&O)", nullptr));
        btnCancel->setText(QCoreApplication::translate("ViewEditor", "Cancel(&C)", nullptr));
        btnApply->setText(QCoreApplication::translate("ViewEditor", "Apply(&A)", nullptr));
        btnAddNode->setText(QCoreApplication::translate("ViewEditor", "Add Node", nullptr));
        label_2->setText(QCoreApplication::translate("ViewEditor", "Node Name:", nullptr));
        label_8->setText(QCoreApplication::translate("ViewEditor", "shortcut key:", nullptr));
        btnDeleteNode->setText(QCoreApplication::translate("ViewEditor", "Delete Node", nullptr));
        btnAddSeperator->setText(QCoreApplication::translate("ViewEditor", "Add Separator", nullptr));
        chkMenuCheckable->setText(QCoreApplication::translate("ViewEditor", "Checkable", nullptr));
        cbMenuAuthority->setItemText(0, QCoreApplication::translate("ViewEditor", "Developor Level1", nullptr));
        cbMenuAuthority->setItemText(1, QCoreApplication::translate("ViewEditor", "Developor Level2", nullptr));
        cbMenuAuthority->setItemText(2, QCoreApplication::translate("ViewEditor", "Developor Level3", nullptr));
        cbMenuAuthority->setItemText(3, QCoreApplication::translate("ViewEditor", "Manager Level1", nullptr));
        cbMenuAuthority->setItemText(4, QCoreApplication::translate("ViewEditor", "Manager Level2", nullptr));
        cbMenuAuthority->setItemText(5, QCoreApplication::translate("ViewEditor", "Manager Level3", nullptr));
        cbMenuAuthority->setItemText(6, QCoreApplication::translate("ViewEditor", "User Level1", nullptr));
        cbMenuAuthority->setItemText(7, QCoreApplication::translate("ViewEditor", "User Level2", nullptr));
        cbMenuAuthority->setItemText(8, QCoreApplication::translate("ViewEditor", "User Level3", nullptr));
        cbMenuAuthority->setItemText(9, QCoreApplication::translate("ViewEditor", "Guest", nullptr));

        label->setText(QCoreApplication::translate("ViewEditor", "Authority:", nullptr));
        groupBox_2->setTitle(QString());
        btnUp->setText(QCoreApplication::translate("ViewEditor", "Up", nullptr));
        btnLeft->setText(QCoreApplication::translate("ViewEditor", "Left", nullptr));
        btnDown->setText(QCoreApplication::translate("ViewEditor", "Down", nullptr));
        btnRight->setText(QCoreApplication::translate("ViewEditor", "Right", nullptr));
        btnIconFinder->setText(QCoreApplication::translate("ViewEditor", "Load Icon", nullptr));
        btnLoadAction->setText(QCoreApplication::translate("ViewEditor", "Load Action", nullptr));
        btnClearAction->setText(QCoreApplication::translate("ViewEditor", "Clear Aaction", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeMenuEdit->headerItem();
        ___qtreewidgetitem->setText(5, QCoreApplication::translate("ViewEditor", "\345\244\207\346\263\250", nullptr));
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("ViewEditor", "Action", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("ViewEditor", "\347\273\204\344\273\266ID", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ViewEditor", "\345\233\276\346\240\207\350\267\257\345\276\204", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ViewEditor", "\345\277\253\346\215\267\351\224\256", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ViewEditor", "\350\217\234\345\215\225\346\240\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("ViewEditor", "MenuBar", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ViewEditor", "ToolBar Editor", nullptr));
        label_3->setText(QCoreApplication::translate("ViewEditor", "Action From Menu:", nullptr));
        btnAddAction_Toolbar->setText(QCoreApplication::translate("ViewEditor", "Add Action", nullptr));
        btnAddSeperator_Toolbar->setText(QCoreApplication::translate("ViewEditor", "Add Seperator", nullptr));
        btnDeleteItem_Toolbar->setText(QCoreApplication::translate("ViewEditor", "Delete Item", nullptr));
        btnAddWidget_Toolbar->setText(QCoreApplication::translate("ViewEditor", "Add Widget", nullptr));
        label_4->setText(QCoreApplication::translate("ViewEditor", "Toolbar height:", nullptr));
        label_5->setText(QCoreApplication::translate("ViewEditor", "Item Width:", nullptr));
        label_6->setText(QCoreApplication::translate("ViewEditor", "Item Height:", nullptr));
        btnMoveDown_Toolbar->setText(QCoreApplication::translate("ViewEditor", "Down", nullptr));
        btnMoveUp_Toolbar->setText(QCoreApplication::translate("ViewEditor", "Up", nullptr));
        btnAddToolbar->setText(QCoreApplication::translate("ViewEditor", "Add Bar", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ViewEditor", "StatusBar Editor", nullptr));
        btnDeleteItem_Statusbar->setText(QCoreApplication::translate("ViewEditor", "Delete Item", nullptr));
        btnAddWidget_Statusbar->setText(QCoreApplication::translate("ViewEditor", "Add Widget", nullptr));
        label_9->setText(QCoreApplication::translate("ViewEditor", "Statusbar height:", nullptr));
        label_10->setText(QCoreApplication::translate("ViewEditor", "Item Width:", nullptr));
        label_11->setText(QCoreApplication::translate("ViewEditor", "Item Height:", nullptr));
        btnMoveDown_Statusbar->setText(QCoreApplication::translate("ViewEditor", "Down", nullptr));
        btnMoveUp_Statusbar->setText(QCoreApplication::translate("ViewEditor", "Up", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("ViewEditor", "ToolBar && StatusBar", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("ViewEditor", "Workspace", nullptr));
        chb_IsShowStatusBar->setText(QCoreApplication::translate("ViewEditor", "Show status-bar", nullptr));
        chb_IsShowMenu->setText(QCoreApplication::translate("ViewEditor", "Show menu-bar", nullptr));
        chb_IsShowToolBar->setText(QCoreApplication::translate("ViewEditor", "Show tool-bar", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("ViewEditor", "Utility", nullptr));
        groupBox->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class ViewEditor: public Ui_ViewEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWEDITOR_H
