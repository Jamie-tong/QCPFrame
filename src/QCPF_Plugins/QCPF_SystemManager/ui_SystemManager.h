/********************************************************************************
** Form generated from reading UI file 'SystemManager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMMANAGER_H
#define UI_SYSTEMMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemManager
{
public:
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QPushButton *btnCancel;
    QPushButton *btnOk;
    QWidget *widget;
    QPushButton *btnUpdate;
    QTabWidget *tabPlugin_Sort;
    QWidget *tabPluginLst;
    QGridLayout *gridLayout_2;
    QTableWidget *tablePluginLst;
    QWidget *tabOrder;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QWidget *widget_3;
    QPushButton *btnOrigPluginMoveDown;
    QPushButton *btnOrigPluginMoveUp;
    QTableWidget *tableOrigPluginsSort;
    QWidget *tab;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *txtSystemID;
    QLineEdit *txtSystemName;

    void setupUi(QDialog *SystemManager)
    {
        if (SystemManager->objectName().isEmpty())
            SystemManager->setObjectName(QString::fromUtf8("SystemManager"));
        SystemManager->resize(1024, 662);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tool/icons/Images/config.png"), QSize(), QIcon::Normal, QIcon::Off);
        SystemManager->setWindowIcon(icon);
        gridLayout_6 = new QGridLayout(SystemManager);
        gridLayout_6->setSpacing(2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(4, 2, 4, 6);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        widget_2 = new QWidget(SystemManager);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        btnCancel = new QPushButton(widget_2);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(110, 4, 100, 35));
        btnCancel->setMinimumSize(QSize(0, 35));
        btnOk = new QPushButton(widget_2);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(5, 4, 100, 35));
        btnOk->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(widget_2, 0, 2, 1, 1);

        widget = new QWidget(SystemManager);
        widget->setObjectName(QString::fromUtf8("widget"));
        btnUpdate = new QPushButton(widget);
        btnUpdate->setObjectName(QString::fromUtf8("btnUpdate"));
        btnUpdate->setGeometry(QRect(1, 4, 100, 35));
        btnUpdate->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        gridLayout->setColumnMinimumWidth(0, 110);
        gridLayout->setColumnMinimumWidth(2, 216);

        gridLayout_5->addLayout(gridLayout, 1, 0, 1, 1);

        tabPlugin_Sort = new QTabWidget(SystemManager);
        tabPlugin_Sort->setObjectName(QString::fromUtf8("tabPlugin_Sort"));
        tabPlugin_Sort->setDocumentMode(true);
        tabPlugin_Sort->setTabsClosable(false);
        tabPluginLst = new QWidget();
        tabPluginLst->setObjectName(QString::fromUtf8("tabPluginLst"));
        gridLayout_2 = new QGridLayout(tabPluginLst);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 6, 2);
        tablePluginLst = new QTableWidget(tabPluginLst);
        if (tablePluginLst->columnCount() < 8)
            tablePluginLst->setColumnCount(8);
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
        tablePluginLst->setColumnCount(8);
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
        tabOrder = new QWidget();
        tabOrder->setObjectName(QString::fromUtf8("tabOrder"));
        gridLayout_4 = new QGridLayout(tabOrder);
        gridLayout_4->setSpacing(2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(2, 2, 2, 2);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget_3 = new QWidget(tabOrder);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        btnOrigPluginMoveDown = new QPushButton(widget_3);
        btnOrigPluginMoveDown->setObjectName(QString::fromUtf8("btnOrigPluginMoveDown"));
        btnOrigPluginMoveDown->setGeometry(QRect(3, 296, 71, 282));
        btnOrigPluginMoveUp = new QPushButton(widget_3);
        btnOrigPluginMoveUp->setObjectName(QString::fromUtf8("btnOrigPluginMoveUp"));
        btnOrigPluginMoveUp->setGeometry(QRect(3, -1, 71, 282));

        gridLayout_3->addWidget(widget_3, 0, 1, 1, 1);

        tableOrigPluginsSort = new QTableWidget(tabOrder);
        if (tableOrigPluginsSort->columnCount() < 2)
            tableOrigPluginsSort->setColumnCount(2);
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
        tableOrigPluginsSort->setColumnCount(2);
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

        gridLayout_3->addWidget(tableOrigPluginsSort, 0, 0, 1, 1);

        gridLayout_3->setColumnMinimumWidth(1, 80);

        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        tabPlugin_Sort->addTab(tabOrder, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 111, 16));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 100, 111, 16));
        txtSystemID = new QLineEdit(tab);
        txtSystemID->setObjectName(QString::fromUtf8("txtSystemID"));
        txtSystemID->setGeometry(QRect(30, 50, 251, 20));
        txtSystemName = new QLineEdit(tab);
        txtSystemName->setObjectName(QString::fromUtf8("txtSystemName"));
        txtSystemName->setGeometry(QRect(30, 120, 251, 20));
        tabPlugin_Sort->addTab(tab, QString());

        gridLayout_5->addWidget(tabPlugin_Sort, 0, 0, 1, 1);

        gridLayout_5->setRowMinimumHeight(1, 43);

        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);


        retranslateUi(SystemManager);

        tabPlugin_Sort->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SystemManager);
    } // setupUi

    void retranslateUi(QDialog *SystemManager)
    {
        SystemManager->setWindowTitle(QCoreApplication::translate("SystemManager", "System Manager", nullptr));
        btnCancel->setText(QCoreApplication::translate("SystemManager", "Cancel(&C)", nullptr));
        btnOk->setText(QCoreApplication::translate("SystemManager", "Ok(&O)", nullptr));
        btnUpdate->setText(QCoreApplication::translate("SystemManager", "Update(&U)", nullptr));
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tabPluginLst), QCoreApplication::translate("SystemManager", "System module info", nullptr));
        btnOrigPluginMoveDown->setText(QCoreApplication::translate("SystemManager", "DOWN", nullptr));
        btnOrigPluginMoveUp->setText(QCoreApplication::translate("SystemManager", "UP", nullptr));
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tabOrder), QCoreApplication::translate("SystemManager", "System module ordering", nullptr));
        label->setText(QCoreApplication::translate("SystemManager", "System ID:", nullptr));
        label_2->setText(QCoreApplication::translate("SystemManager", "System Name:", nullptr));
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tab), QCoreApplication::translate("SystemManager", "Utility", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SystemManager: public Ui_SystemManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMMANAGER_H
