/********************************************************************************
** Form generated from reading UI file 'SystemManager.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMMANAGER_H
#define UI_SYSTEMMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemManager
{
public:
    QTabWidget *tabPlugin_Sort;
    QWidget *tabPluginLst;
    QTableWidget *tablePluginLst;
    QWidget *tab_2;
    QTableWidget *tableOrigPluginsSort;
    QPushButton *btnOrigPluginMoveDown;
    QPushButton *btnOrigPluginMoveUp;
    QWidget *tab;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *txtSystemID;
    QLineEdit *txtSystemName;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QPushButton *btnUpdate;
    QGroupBox *groupBox;

    void setupUi(QDialog *SystemManager)
    {
        if (SystemManager->objectName().isEmpty())
            SystemManager->setObjectName(QString::fromUtf8("SystemManager"));
        SystemManager->resize(950, 670);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tool/icons/Images/config.png"), QSize(), QIcon::Normal, QIcon::Off);
        SystemManager->setWindowIcon(icon);
        tabPlugin_Sort = new QTabWidget(SystemManager);
        tabPlugin_Sort->setObjectName(QString::fromUtf8("tabPlugin_Sort"));
        tabPlugin_Sort->setGeometry(QRect(5, 6, 961, 611));
        tabPlugin_Sort->setDocumentMode(true);
        tabPlugin_Sort->setTabsClosable(false);
        tabPluginLst = new QWidget();
        tabPluginLst->setObjectName(QString::fromUtf8("tabPluginLst"));
        tablePluginLst = new QTableWidget(tabPluginLst);
        if (tablePluginLst->columnCount() < 8)
            tablePluginLst->setColumnCount(8);
        if (tablePluginLst->rowCount() < 26)
            tablePluginLst->setRowCount(26);
        tablePluginLst->setObjectName(QString::fromUtf8("tablePluginLst"));
        tablePluginLst->setGeometry(QRect(4, 2, 931, 581));
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
        tabPlugin_Sort->addTab(tabPluginLst, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tableOrigPluginsSort = new QTableWidget(tab_2);
        if (tableOrigPluginsSort->columnCount() < 2)
            tableOrigPluginsSort->setColumnCount(2);
        if (tableOrigPluginsSort->rowCount() < 26)
            tableOrigPluginsSort->setRowCount(26);
        tableOrigPluginsSort->setObjectName(QString::fromUtf8("tableOrigPluginsSort"));
        tableOrigPluginsSort->setGeometry(QRect(2, 2, 861, 581));
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
        btnOrigPluginMoveDown = new QPushButton(tab_2);
        btnOrigPluginMoveDown->setObjectName(QString::fromUtf8("btnOrigPluginMoveDown"));
        btnOrigPluginMoveDown->setGeometry(QRect(869, 293, 71, 291));
        btnOrigPluginMoveUp = new QPushButton(tab_2);
        btnOrigPluginMoveUp->setObjectName(QString::fromUtf8("btnOrigPluginMoveUp"));
        btnOrigPluginMoveUp->setGeometry(QRect(869, 1, 71, 291));
        tabPlugin_Sort->addTab(tab_2, QString());
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
        btnOk = new QPushButton(SystemManager);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(735, 624, 100, 35));
        btnOk->setMinimumSize(QSize(0, 35));
        btnCancel = new QPushButton(SystemManager);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(840, 624, 100, 35));
        btnCancel->setMinimumSize(QSize(0, 35));
        btnUpdate = new QPushButton(SystemManager);
        btnUpdate->setObjectName(QString::fromUtf8("btnUpdate"));
        btnUpdate->setGeometry(QRect(9, 624, 100, 35));
        btnUpdate->setMinimumSize(QSize(0, 35));
        groupBox = new QGroupBox(SystemManager);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(-30, 615, 1000, 2));
        groupBox->setFlat(true);

        retranslateUi(SystemManager);

        tabPlugin_Sort->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SystemManager);
    } // setupUi

    void retranslateUi(QDialog *SystemManager)
    {
        SystemManager->setWindowTitle(QCoreApplication::translate("SystemManager", "System Manager", nullptr));
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tabPluginLst), QCoreApplication::translate("SystemManager", "System module info", nullptr));
        btnOrigPluginMoveDown->setText(QCoreApplication::translate("SystemManager", "DOWN", nullptr));
        btnOrigPluginMoveUp->setText(QCoreApplication::translate("SystemManager", "UP", nullptr));
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tab_2), QCoreApplication::translate("SystemManager", "System module ordering", nullptr));
        label->setText(QCoreApplication::translate("SystemManager", "System ID:", nullptr));
        label_2->setText(QCoreApplication::translate("SystemManager", "System Name:", nullptr));
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tab), QCoreApplication::translate("SystemManager", "Utility", nullptr));
        btnOk->setText(QCoreApplication::translate("SystemManager", "Ok(&O)", nullptr));
        btnCancel->setText(QCoreApplication::translate("SystemManager", "Cancel(&C)", nullptr));
        btnUpdate->setText(QCoreApplication::translate("SystemManager", "Update(&U)", nullptr));
        groupBox->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class SystemManager: public Ui_SystemManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMMANAGER_H
