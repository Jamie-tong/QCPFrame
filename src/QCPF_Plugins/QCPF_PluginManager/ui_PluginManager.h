/********************************************************************************
** Form generated from reading UI file 'PluginManager.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
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
    QTabWidget *tabPlugin_Sort;
    QWidget *tabPluginLst;
    QTableWidget *tablePluginLst;
    QWidget *tab;
    QWidget *verticalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *treePluginClone;
    QVBoxLayout *verticalLayout;
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
    QWidget *tab_2;
    QGroupBox *groupBox;
    QPushButton *btnOrigPluginMoveDown;
    QPushButton *btnOrigPluginMoveUp;
    QTableWidget *tableOrigPluginsSort;
    QGroupBox *groupBox_2;
    QPushButton *btnValidPluginMoveDown;
    QPushButton *btnValidPluginMoveUp;
    QTableWidget *tableAllValidPluginsSort;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QPushButton *btnApply;
    QGroupBox *groupBox_3;

    void setupUi(QDialog *PluginManager)
    {
        if (PluginManager->objectName().isEmpty())
            PluginManager->setObjectName(QString::fromUtf8("PluginManager"));
        PluginManager->resize(950, 670);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../bin/debug/Images/docker.png"), QSize(), QIcon::Normal, QIcon::Off);
        PluginManager->setWindowIcon(icon);
        tabPlugin_Sort = new QTabWidget(PluginManager);
        tabPlugin_Sort->setObjectName(QString::fromUtf8("tabPlugin_Sort"));
        tabPlugin_Sort->setGeometry(QRect(5, 6, 951, 611));
        tabPlugin_Sort->setDocumentMode(true);
        tabPlugin_Sort->setTabsClosable(false);
        tabPluginLst = new QWidget();
        tabPluginLst->setObjectName(QString::fromUtf8("tabPluginLst"));
        tablePluginLst = new QTableWidget(tabPluginLst);
        if (tablePluginLst->columnCount() < 9)
            tablePluginLst->setColumnCount(9);
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
        tabPlugin_Sort->addTab(tabPluginLst, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(1, 1, 941, 581));
        horizontalLayout_2 = new QHBoxLayout(verticalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        treePluginClone = new QTreeWidget(verticalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treePluginClone->setHeaderItem(__qtreewidgetitem);
        treePluginClone->setObjectName(QString::fromUtf8("treePluginClone"));

        horizontalLayout_2->addWidget(treePluginClone);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(verticalLayoutWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setEnabled(true);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        cbOriginPluginLst = new QComboBox(frame);
        cbOriginPluginLst->setObjectName(QString::fromUtf8("cbOriginPluginLst"));
        cbOriginPluginLst->setGeometry(QRect(12, 21, 161, 20));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(12, 2, 151, 15));
        label_2->setMaximumSize(QSize(16777215, 15));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(12, 101, 91, 15));
        label_3->setMaximumSize(QSize(16777215, 15));
        txtCopyID = new QLineEdit(frame);
        txtCopyID->setObjectName(QString::fromUtf8("txtCopyID"));
        txtCopyID->setGeometry(QRect(12, 70, 161, 20));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(12, 51, 161, 15));
        label_5->setMaximumSize(QSize(16777215, 15));
        txtCopyAliasName = new QLineEdit(frame);
        txtCopyAliasName->setObjectName(QString::fromUtf8("txtCopyAliasName"));
        txtCopyAliasName->setGeometry(QRect(12, 120, 161, 20));
        btnClone = new QPushButton(frame);
        btnClone->setObjectName(QString::fromUtf8("btnClone"));
        btnClone->setGeometry(QRect(12, 440, 161, 61));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(12, 150, 91, 15));
        label_6->setMaximumSize(QSize(16777215, 15));
        btnDeleteClone = new QPushButton(frame);
        btnDeleteClone->setObjectName(QString::fromUtf8("btnDeleteClone"));
        btnDeleteClone->setEnabled(false);
        btnDeleteClone->setGeometry(QRect(12, 510, 161, 61));
        txtCopyComment = new QTextEdit(frame);
        txtCopyComment->setObjectName(QString::fromUtf8("txtCopyComment"));
        txtCopyComment->setGeometry(QRect(12, 170, 161, 261));

        verticalLayout->addWidget(frame);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 16);
        horizontalLayout_2->setStretch(1, 4);
        tabPlugin_Sort->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(3, 10, 931, 281));
        btnOrigPluginMoveDown = new QPushButton(groupBox);
        btnOrigPluginMoveDown->setObjectName(QString::fromUtf8("btnOrigPluginMoveDown"));
        btnOrigPluginMoveDown->setGeometry(QRect(870, 150, 51, 121));
        btnOrigPluginMoveUp = new QPushButton(groupBox);
        btnOrigPluginMoveUp->setObjectName(QString::fromUtf8("btnOrigPluginMoveUp"));
        btnOrigPluginMoveUp->setGeometry(QRect(870, 19, 51, 121));
        tableOrigPluginsSort = new QTableWidget(groupBox);
        if (tableOrigPluginsSort->columnCount() < 3)
            tableOrigPluginsSort->setColumnCount(3);
        if (tableOrigPluginsSort->rowCount() < 26)
            tableOrigPluginsSort->setRowCount(26);
        tableOrigPluginsSort->setObjectName(QString::fromUtf8("tableOrigPluginsSort"));
        tableOrigPluginsSort->setGeometry(QRect(10, 20, 851, 251));
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
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(3, 304, 931, 281));
        btnValidPluginMoveDown = new QPushButton(groupBox_2);
        btnValidPluginMoveDown->setObjectName(QString::fromUtf8("btnValidPluginMoveDown"));
        btnValidPluginMoveDown->setGeometry(QRect(870, 150, 51, 121));
        btnValidPluginMoveUp = new QPushButton(groupBox_2);
        btnValidPluginMoveUp->setObjectName(QString::fromUtf8("btnValidPluginMoveUp"));
        btnValidPluginMoveUp->setGeometry(QRect(870, 19, 51, 121));
        tableAllValidPluginsSort = new QTableWidget(groupBox_2);
        if (tableAllValidPluginsSort->columnCount() < 4)
            tableAllValidPluginsSort->setColumnCount(4);
        if (tableAllValidPluginsSort->rowCount() < 26)
            tableAllValidPluginsSort->setRowCount(26);
        tableAllValidPluginsSort->setObjectName(QString::fromUtf8("tableAllValidPluginsSort"));
        tableAllValidPluginsSort->setGeometry(QRect(10, 20, 851, 251));
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
        tabPlugin_Sort->addTab(tab_2, QString());
        btnOk = new QPushButton(PluginManager);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(591, 624, 100, 35));
        btnOk->setMinimumSize(QSize(0, 35));
        btnCancel = new QPushButton(PluginManager);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(832, 624, 100, 35));
        btnCancel->setMinimumSize(QSize(0, 35));
        btnApply = new QPushButton(PluginManager);
        btnApply->setObjectName(QString::fromUtf8("btnApply"));
        btnApply->setGeometry(QRect(691, 624, 100, 35));
        btnApply->setMinimumSize(QSize(0, 35));
        groupBox_3 = new QGroupBox(PluginManager);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(-10, 616, 1000, 2));
        groupBox_3->setFlat(true);

        retranslateUi(PluginManager);

        tabPlugin_Sort->setCurrentIndex(1);


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
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tab), QCoreApplication::translate("PluginManager", "Plugin clone", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PluginManager", "Original plugin order", nullptr));
        btnOrigPluginMoveDown->setText(QCoreApplication::translate("PluginManager", "DOWN", nullptr));
        btnOrigPluginMoveUp->setText(QCoreApplication::translate("PluginManager", "UP", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PluginManager", "All valid plugin order", nullptr));
        btnValidPluginMoveDown->setText(QCoreApplication::translate("PluginManager", "DOWN", nullptr));
        btnValidPluginMoveUp->setText(QCoreApplication::translate("PluginManager", "UP", nullptr));
        tabPlugin_Sort->setTabText(tabPlugin_Sort->indexOf(tab_2), QCoreApplication::translate("PluginManager", "Plugin ordering", nullptr));
        btnOk->setText(QCoreApplication::translate("PluginManager", "Ok(&O)", nullptr));
        btnCancel->setText(QCoreApplication::translate("PluginManager", "Cancel(&C)", nullptr));
        btnApply->setText(QCoreApplication::translate("PluginManager", "Apply(&A)", nullptr));
        groupBox_3->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class PluginManager: public Ui_PluginManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINMANAGER_H
