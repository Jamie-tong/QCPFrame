/********************************************************************************
** Form generated from reading UI file 'PluginManager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINMANAGER_H
#define UI_PLUGINMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PluginManager
{
public:
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout_10;
    QTabWidget *tabPlugin_Sort;
    QWidget *tabPluginLst;
    QGridLayout *gridLayout_2;
    QTableWidget *tablePluginLst;
    QWidget *tabClone;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QTreeWidget *treePluginClone;
    QFrame *frame;
    QComboBox *cbOriginPluginLst;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *txtCopyID;
    QLabel *label_5;
    QLineEdit *txtCopyAliasName;
    QPushButton *btnClone;
    QLabel *label_6;
    QPushButton *btnDeleteClone;
    QTextEdit *txtCopyComment;
    QWidget *tabOrder;
    QGridLayout *gridLayout_9;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QTableWidget *tableOrigPluginsSort;
    QWidget *widget_3;
    QPushButton *btnOrigPluginMoveDown;
    QPushButton *btnOrigPluginMoveUp;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QWidget *widget_4;
    QPushButton *btnValidPluginMoveDown;
    QPushButton *btnValidPluginMoveUp;
    QTableWidget *tableAllValidPluginsSort;
    QGridLayout *gridLayout;
    QWidget *widget;
    QPushButton *btnRefreshPlugins;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QPushButton *btnCancel;
    QPushButton *btnOk;

    void setupUi(QDialog *PluginManager)
    {
        if (PluginManager->objectName().isEmpty())
            PluginManager->setObjectName(QString::fromUtf8("PluginManager"));
        PluginManager->resize(1061, 741);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../bin/debug/Images/docker.png"), QSize(), QIcon::Normal, QIcon::Off);
        PluginManager->setWindowIcon(icon);
        gridLayout_11 = new QGridLayout(PluginManager);
        gridLayout_11->setSpacing(2);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(2, 2, 2, 2);
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        tabPlugin_Sort = new QTabWidget(PluginManager);
        tabPlugin_Sort->setObjectName(QString::fromUtf8("tabPlugin_Sort"));
        tabPlugin_Sort->setDocumentMode(true);
        tabPlugin_Sort->setTabsClosable(false);
        tabPluginLst = new QWidget();
        tabPluginLst->setObjectName(QString::fromUtf8("tabPluginLst"));
        gridLayout_2 = new QGridLayout(tabPluginLst);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(6, 2, 6, 2);
        tablePluginLst = new QTableWidget(tabPluginLst);
        if (tablePluginLst->columnCount() < 9)
            tablePluginLst->setColumnCount(9);
        if (tablePluginLst->rowCount() < 26)
            tablePluginLst->setRowCount(26);
        tablePluginLst->setObjectName(QString::fromUtf8("tablePluginLst"));
        tablePluginLst->setMouseTracking(false);
        tablePluginLst->setAutoFillBackground(false);
        tablePluginLst->setStyleSheet(QString::fromUtf8(""));
        tablePluginLst->setFrameShape(QFrame::StyledPanel);
        tablePluginLst->setFrameShadow(QFrame::Plain);
        tablePluginLst->setAutoScroll(true);
        tablePluginLst->setProperty("showDropIndicator", QVariant(true));
        tablePluginLst->setAlternatingRowColors(true);
        tablePluginLst->setSelectionMode(QAbstractItemView::MultiSelection);
        tablePluginLst->setSelectionBehavior(QAbstractItemView::SelectRows);
        tablePluginLst->setShowGrid(true);
        tablePluginLst->setGridStyle(Qt::SolidLine);
        tablePluginLst->setWordWrap(true);
        tablePluginLst->setRowCount(26);
        tablePluginLst->setColumnCount(9);
        tablePluginLst->horizontalHeader()->setVisible(false);
        tablePluginLst->horizontalHeader()->setCascadingSectionResizes(false);
        tablePluginLst->horizontalHeader()->setDefaultSectionSize(60);
        tablePluginLst->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tablePluginLst->horizontalHeader()->setStretchLastSection(true);
        tablePluginLst->verticalHeader()->setVisible(false);
        tablePluginLst->verticalHeader()->setCascadingSectionResizes(false);
        tablePluginLst->verticalHeader()->setMinimumSectionSize(18);
        tablePluginLst->verticalHeader()->setDefaultSectionSize(18);
        tablePluginLst->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tablePluginLst->verticalHeader()->setStretchLastSection(false);

        gridLayout_2->addWidget(tablePluginLst, 0, 0, 1, 1);

        tabPlugin_Sort->addTab(tabPluginLst, QString());
        tabClone = new QWidget();
        tabClone->setObjectName(QString::fromUtf8("tabClone"));
        gridLayout_4 = new QGridLayout(tabClone);
        gridLayout_4->setSpacing(2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(6, 2, 6, 2);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        treePluginClone = new QTreeWidget(tabClone);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treePluginClone->setHeaderItem(__qtreewidgetitem);
        treePluginClone->setObjectName(QString::fromUtf8("treePluginClone"));

        gridLayout_3->addWidget(treePluginClone, 0, 0, 1, 1);

        frame = new QFrame(tabClone);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setEnabled(true);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        cbOriginPluginLst = new QComboBox(frame);
        cbOriginPluginLst->setObjectName(QString::fromUtf8("cbOriginPluginLst"));
        cbOriginPluginLst->setGeometry(QRect(5, 21, 161, 20));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(5, 2, 151, 15));
        label_2->setMaximumSize(QSize(16777215, 15));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(5, 101, 91, 15));
        label_3->setMaximumSize(QSize(16777215, 15));
        txtCopyID = new QLineEdit(frame);
        txtCopyID->setObjectName(QString::fromUtf8("txtCopyID"));
        txtCopyID->setGeometry(QRect(5, 70, 161, 20));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(5, 51, 161, 15));
        label_5->setMaximumSize(QSize(16777215, 15));
        txtCopyAliasName = new QLineEdit(frame);
        txtCopyAliasName->setObjectName(QString::fromUtf8("txtCopyAliasName"));
        txtCopyAliasName->setGeometry(QRect(5, 120, 161, 20));
        btnClone = new QPushButton(frame);
        btnClone->setObjectName(QString::fromUtf8("btnClone"));
        btnClone->setGeometry(QRect(5, 440, 161, 61));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(5, 150, 91, 15));
        label_6->setMaximumSize(QSize(16777215, 15));
        btnDeleteClone = new QPushButton(frame);
        btnDeleteClone->setObjectName(QString::fromUtf8("btnDeleteClone"));
        btnDeleteClone->setEnabled(false);
        btnDeleteClone->setGeometry(QRect(5, 510, 161, 61));
        txtCopyComment = new QTextEdit(frame);
        txtCopyComment->setObjectName(QString::fromUtf8("txtCopyComment"));
        txtCopyComment->setGeometry(QRect(5, 170, 161, 261));

        gridLayout_3->addWidget(frame, 0, 1, 1, 1);

        gridLayout_3->setColumnMinimumWidth(1, 170);

        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        tabPlugin_Sort->addTab(tabClone, QString());
        tabOrder = new QWidget();
        tabOrder->setObjectName(QString::fromUtf8("tabOrder"));
        gridLayout_9 = new QGridLayout(tabOrder);
        gridLayout_9->setSpacing(2);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(4, 2, 4, 2);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tabOrder);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setSpacing(2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(2, 2, 2, 2);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tableOrigPluginsSort = new QTableWidget(groupBox);
        if (tableOrigPluginsSort->columnCount() < 3)
            tableOrigPluginsSort->setColumnCount(3);
        if (tableOrigPluginsSort->rowCount() < 26)
            tableOrigPluginsSort->setRowCount(26);
        tableOrigPluginsSort->setObjectName(QString::fromUtf8("tableOrigPluginsSort"));
        tableOrigPluginsSort->setMouseTracking(false);
        tableOrigPluginsSort->setAutoFillBackground(false);
        tableOrigPluginsSort->setStyleSheet(QString::fromUtf8(""));
        tableOrigPluginsSort->setFrameShape(QFrame::StyledPanel);
        tableOrigPluginsSort->setFrameShadow(QFrame::Plain);
        tableOrigPluginsSort->setAutoScroll(true);
        tableOrigPluginsSort->setProperty("showDropIndicator", QVariant(true));
        tableOrigPluginsSort->setAlternatingRowColors(true);
        tableOrigPluginsSort->setSelectionMode(QAbstractItemView::MultiSelection);
        tableOrigPluginsSort->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableOrigPluginsSort->setShowGrid(true);
        tableOrigPluginsSort->setGridStyle(Qt::SolidLine);
        tableOrigPluginsSort->setWordWrap(true);
        tableOrigPluginsSort->setRowCount(26);
        tableOrigPluginsSort->setColumnCount(3);
        tableOrigPluginsSort->horizontalHeader()->setCascadingSectionResizes(false);
        tableOrigPluginsSort->horizontalHeader()->setDefaultSectionSize(60);
        tableOrigPluginsSort->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableOrigPluginsSort->horizontalHeader()->setStretchLastSection(true);
        tableOrigPluginsSort->verticalHeader()->setVisible(false);
        tableOrigPluginsSort->verticalHeader()->setCascadingSectionResizes(false);
        tableOrigPluginsSort->verticalHeader()->setMinimumSectionSize(18);
        tableOrigPluginsSort->verticalHeader()->setDefaultSectionSize(18);
        tableOrigPluginsSort->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableOrigPluginsSort->verticalHeader()->setStretchLastSection(false);

        gridLayout_5->addWidget(tableOrigPluginsSort, 0, 0, 1, 1);

        widget_3 = new QWidget(groupBox);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        btnOrigPluginMoveDown = new QPushButton(widget_3);
        btnOrigPluginMoveDown->setObjectName(QString::fromUtf8("btnOrigPluginMoveDown"));
        btnOrigPluginMoveDown->setGeometry(QRect(4, 130, 51, 121));
        btnOrigPluginMoveUp = new QPushButton(widget_3);
        btnOrigPluginMoveUp->setObjectName(QString::fromUtf8("btnOrigPluginMoveUp"));
        btnOrigPluginMoveUp->setGeometry(QRect(4, -1, 51, 121));

        gridLayout_5->addWidget(widget_3, 0, 1, 1, 1);

        gridLayout_5->setColumnMinimumWidth(1, 60);

        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tabOrder);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_8 = new QGridLayout(groupBox_2);
        gridLayout_8->setSpacing(2);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(2, 2, 2, 2);
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(2);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        widget_4 = new QWidget(groupBox_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        btnValidPluginMoveDown = new QPushButton(widget_4);
        btnValidPluginMoveDown->setObjectName(QString::fromUtf8("btnValidPluginMoveDown"));
        btnValidPluginMoveDown->setGeometry(QRect(4, 130, 51, 121));
        btnValidPluginMoveUp = new QPushButton(widget_4);
        btnValidPluginMoveUp->setObjectName(QString::fromUtf8("btnValidPluginMoveUp"));
        btnValidPluginMoveUp->setGeometry(QRect(4, -1, 51, 121));

        gridLayout_7->addWidget(widget_4, 0, 1, 1, 1);

        tableAllValidPluginsSort = new QTableWidget(groupBox_2);
        if (tableAllValidPluginsSort->columnCount() < 4)
            tableAllValidPluginsSort->setColumnCount(4);
        if (tableAllValidPluginsSort->rowCount() < 26)
            tableAllValidPluginsSort->setRowCount(26);
        tableAllValidPluginsSort->setObjectName(QString::fromUtf8("tableAllValidPluginsSort"));
        tableAllValidPluginsSort->setMouseTracking(false);
        tableAllValidPluginsSort->setAutoFillBackground(false);
        tableAllValidPluginsSort->setStyleSheet(QString::fromUtf8(""));
        tableAllValidPluginsSort->setFrameShape(QFrame::StyledPanel);
        tableAllValidPluginsSort->setFrameShadow(QFrame::Plain);
        tableAllValidPluginsSort->setAutoScroll(true);
        tableAllValidPluginsSort->setProperty("showDropIndicator", QVariant(true));
        tableAllValidPluginsSort->setAlternatingRowColors(true);
        tableAllValidPluginsSort->setSelectionMode(QAbstractItemView::MultiSelection);
        tableAllValidPluginsSort->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableAllValidPluginsSort->setShowGrid(true);
        tableAllValidPluginsSort->setGridStyle(Qt::SolidLine);
        tableAllValidPluginsSort->setWordWrap(true);
        tableAllValidPluginsSort->setRowCount(26);
        tableAllValidPluginsSort->setColumnCount(4);
        tableAllValidPluginsSort->horizontalHeader()->setCascadingSectionResizes(false);
        tableAllValidPluginsSort->horizontalHeader()->setDefaultSectionSize(60);
        tableAllValidPluginsSort->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableAllValidPluginsSort->horizontalHeader()->setStretchLastSection(true);
        tableAllValidPluginsSort->verticalHeader()->setVisible(false);
        tableAllValidPluginsSort->verticalHeader()->setCascadingSectionResizes(false);
        tableAllValidPluginsSort->verticalHeader()->setMinimumSectionSize(18);
        tableAllValidPluginsSort->verticalHeader()->setDefaultSectionSize(18);
        tableAllValidPluginsSort->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableAllValidPluginsSort->verticalHeader()->setStretchLastSection(false);

        gridLayout_7->addWidget(tableAllValidPluginsSort, 0, 0, 1, 1);

        gridLayout_7->setColumnMinimumWidth(1, 60);

        gridLayout_8->addLayout(gridLayout_7, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);


        gridLayout_9->addLayout(verticalLayout, 0, 0, 1, 1);

        tabPlugin_Sort->addTab(tabOrder, QString());

        gridLayout_10->addWidget(tabPlugin_Sort, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(PluginManager);
        widget->setObjectName(QString::fromUtf8("widget"));
        btnRefreshPlugins = new QPushButton(widget);
        btnRefreshPlugins->setObjectName(QString::fromUtf8("btnRefreshPlugins"));
        btnRefreshPlugins->setGeometry(QRect(6, 4, 100, 35));
        btnRefreshPlugins->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        widget_2 = new QWidget(PluginManager);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        btnCancel = new QPushButton(widget_2);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(105, 4, 100, 35));
        btnCancel->setMinimumSize(QSize(0, 35));
        btnOk = new QPushButton(widget_2);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(3, 4, 100, 35));
        btnOk->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(widget_2, 0, 2, 1, 1);

        gridLayout->setColumnMinimumWidth(0, 106);
        gridLayout->setColumnMinimumWidth(2, 216);

        gridLayout_10->addLayout(gridLayout, 1, 0, 1, 1);

        gridLayout_10->setRowMinimumHeight(1, 44);

        gridLayout_11->addLayout(gridLayout_10, 0, 0, 1, 1);


        retranslateUi(PluginManager);

        tabPlugin_Sort->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PluginManager);
    } // setupUi

    void retranslateUi(QDialog *PluginManager)
    {
        PluginManager->setWindowTitle(QCoreApplication::translate("PluginManager", "Plugin Manager", nullptr));
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tabPluginLst), QCoreApplication::translate("PluginManager", "Plugin info", nullptr));
        label_2->setText(QCoreApplication::translate("PluginManager", "Original Plugin ID:", nullptr));
        label_3->setText(QCoreApplication::translate("PluginManager", "Copy Alias:", nullptr));
        label_5->setText(QCoreApplication::translate("PluginManager", "Copy ID:", nullptr));
        btnClone->setText(QCoreApplication::translate("PluginManager", "Clone(&L)", nullptr));
        label_6->setText(QCoreApplication::translate("PluginManager", "Copy Detail:", nullptr));
        btnDeleteClone->setText(QCoreApplication::translate("PluginManager", "Destroy(&D)", nullptr));
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tabClone), QCoreApplication::translate("PluginManager", "Plugin clone", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PluginManager", "Original plugin order", nullptr));
        btnOrigPluginMoveDown->setText(QCoreApplication::translate("PluginManager", "DOWN", nullptr));
        btnOrigPluginMoveUp->setText(QCoreApplication::translate("PluginManager", "UP", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PluginManager", "All valid plugin order", nullptr));
        btnValidPluginMoveDown->setText(QCoreApplication::translate("PluginManager", "DOWN", nullptr));
        btnValidPluginMoveUp->setText(QCoreApplication::translate("PluginManager", "UP", nullptr));
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tabOrder), QCoreApplication::translate("PluginManager", "Plugin ordering", nullptr));
        btnRefreshPlugins->setText(QCoreApplication::translate("PluginManager", "Update(&U)", nullptr));
        btnCancel->setText(QCoreApplication::translate("PluginManager", "Cancel(&C)", nullptr));
        btnOk->setText(QCoreApplication::translate("PluginManager", "Ok(&O)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PluginManager: public Ui_PluginManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINMANAGER_H
