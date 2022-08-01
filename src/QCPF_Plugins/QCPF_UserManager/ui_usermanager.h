/********************************************************************************
** Form generated from reading UI file 'usermanager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMANAGER_H
#define UI_USERMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_UserManager
{
public:
    QGroupBox *groupBox;
    QTableWidget *tableUserInfo;
    QGroupBox *groupBox_2;
    QLineEdit *txtPassword;
    QLabel *label;
    QLineEdit *txtUserName;
    QLabel *label_2;
    QComboBox *cbAuthority;
    QLabel *label_3;
    QGroupBox *groupBox_3;
    QPushButton *btnAddUserInfo;
    QPushButton *btnReplaceUserInfo;
    QPushButton *btnDeleteUserInfo;
    QGroupBox *groupBox_4;
    QPushButton *btnCancel;
    QPushButton *btnOk;

    void setupUi(QDialog *UserManager)
    {
        if (UserManager->objectName().isEmpty())
            UserManager->setObjectName(QString::fromUtf8("UserManager"));
        UserManager->resize(770, 500);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../bin/Images/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        UserManager->setWindowIcon(icon);
        groupBox = new QGroupBox(UserManager);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(5, 6, 586, 481));
        tableUserInfo = new QTableWidget(groupBox);
        if (tableUserInfo->columnCount() < 4)
            tableUserInfo->setColumnCount(4);
        if (tableUserInfo->rowCount() < 25)
            tableUserInfo->setRowCount(25);
        tableUserInfo->setObjectName(QString::fromUtf8("tableUserInfo"));
        tableUserInfo->setGeometry(QRect(7, 19, 571, 451));
        tableUserInfo->setMouseTracking(false);
        tableUserInfo->setAutoFillBackground(false);
        tableUserInfo->setStyleSheet(QString::fromUtf8(""));
        tableUserInfo->setFrameShape(QFrame::StyledPanel);
        tableUserInfo->setFrameShadow(QFrame::Plain);
        tableUserInfo->setAutoScroll(true);
        tableUserInfo->setProperty("showDropIndicator", QVariant(true));
        tableUserInfo->setAlternatingRowColors(true);
        tableUserInfo->setSelectionMode(QAbstractItemView::MultiSelection);
        tableUserInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableUserInfo->setShowGrid(true);
        tableUserInfo->setGridStyle(Qt::SolidLine);
        tableUserInfo->setWordWrap(true);
        tableUserInfo->setRowCount(25);
        tableUserInfo->setColumnCount(4);
        tableUserInfo->horizontalHeader()->setVisible(false);
        tableUserInfo->horizontalHeader()->setCascadingSectionResizes(false);
        tableUserInfo->horizontalHeader()->setDefaultSectionSize(60);
        tableUserInfo->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableUserInfo->horizontalHeader()->setStretchLastSection(true);
        tableUserInfo->verticalHeader()->setVisible(false);
        tableUserInfo->verticalHeader()->setCascadingSectionResizes(false);
        tableUserInfo->verticalHeader()->setMinimumSectionSize(18);
        tableUserInfo->verticalHeader()->setDefaultSectionSize(18);
        tableUserInfo->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableUserInfo->verticalHeader()->setStretchLastSection(false);
        groupBox_2 = new QGroupBox(UserManager);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(599, 13, 161, 171));
        txtPassword = new QLineEdit(groupBox_2);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setGeometry(QRect(10, 80, 141, 20));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 81, 16));
        txtUserName = new QLineEdit(groupBox_2);
        txtUserName->setObjectName(QString::fromUtf8("txtUserName"));
        txtUserName->setGeometry(QRect(10, 30, 141, 20));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 60, 81, 16));
        cbAuthority = new QComboBox(groupBox_2);
        cbAuthority->addItem(QString());
        cbAuthority->addItem(QString());
        cbAuthority->addItem(QString());
        cbAuthority->addItem(QString());
        cbAuthority->addItem(QString());
        cbAuthority->addItem(QString());
        cbAuthority->addItem(QString());
        cbAuthority->addItem(QString());
        cbAuthority->addItem(QString());
        cbAuthority->addItem(QString());
        cbAuthority->setObjectName(QString::fromUtf8("cbAuthority"));
        cbAuthority->setGeometry(QRect(10, 135, 141, 22));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 115, 71, 16));
        groupBox_3 = new QGroupBox(UserManager);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(600, 200, 161, 161));
        btnAddUserInfo = new QPushButton(groupBox_3);
        btnAddUserInfo->setObjectName(QString::fromUtf8("btnAddUserInfo"));
        btnAddUserInfo->setGeometry(QRect(10, 10, 141, 41));
        btnReplaceUserInfo = new QPushButton(groupBox_3);
        btnReplaceUserInfo->setObjectName(QString::fromUtf8("btnReplaceUserInfo"));
        btnReplaceUserInfo->setGeometry(QRect(10, 60, 141, 41));
        btnDeleteUserInfo = new QPushButton(groupBox_3);
        btnDeleteUserInfo->setObjectName(QString::fromUtf8("btnDeleteUserInfo"));
        btnDeleteUserInfo->setGeometry(QRect(10, 110, 141, 41));
        groupBox_4 = new QGroupBox(UserManager);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(600, 376, 161, 111));
        btnCancel = new QPushButton(groupBox_4);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(10, 60, 141, 41));
        btnOk = new QPushButton(groupBox_4);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(10, 10, 141, 41));

        retranslateUi(UserManager);

        cbAuthority->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(UserManager);
    } // setupUi

    void retranslateUi(QDialog *UserManager)
    {
        UserManager->setWindowTitle(QCoreApplication::translate("UserManager", "User Manager", nullptr));
        groupBox->setTitle(QCoreApplication::translate("UserManager", "User Info", nullptr));
        groupBox_2->setTitle(QString());
        label->setText(QCoreApplication::translate("UserManager", "User Name:", nullptr));
        label_2->setText(QCoreApplication::translate("UserManager", "Password:", nullptr));
        cbAuthority->setItemText(0, QCoreApplication::translate("UserManager", "Developor Level1", nullptr));
        cbAuthority->setItemText(1, QCoreApplication::translate("UserManager", "Developor Level2", nullptr));
        cbAuthority->setItemText(2, QCoreApplication::translate("UserManager", "Developor Level3", nullptr));
        cbAuthority->setItemText(3, QCoreApplication::translate("UserManager", "Manager Level1", nullptr));
        cbAuthority->setItemText(4, QCoreApplication::translate("UserManager", "Manager Level2", nullptr));
        cbAuthority->setItemText(5, QCoreApplication::translate("UserManager", "Manager Level3", nullptr));
        cbAuthority->setItemText(6, QCoreApplication::translate("UserManager", "User Level1", nullptr));
        cbAuthority->setItemText(7, QCoreApplication::translate("UserManager", "User Level2", nullptr));
        cbAuthority->setItemText(8, QCoreApplication::translate("UserManager", "User Level3", nullptr));
        cbAuthority->setItemText(9, QCoreApplication::translate("UserManager", "Guest", nullptr));

        label_3->setText(QCoreApplication::translate("UserManager", "Authority:", nullptr));
        groupBox_3->setTitle(QString());
        btnAddUserInfo->setText(QCoreApplication::translate("UserManager", "Add User Info", nullptr));
        btnReplaceUserInfo->setText(QCoreApplication::translate("UserManager", "Replace User Info", nullptr));
        btnDeleteUserInfo->setText(QCoreApplication::translate("UserManager", "Delete User Info", nullptr));
        groupBox_4->setTitle(QString());
        btnCancel->setText(QCoreApplication::translate("UserManager", "Cancel(&C)", nullptr));
        btnOk->setText(QCoreApplication::translate("UserManager", "Ok(&O)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserManager: public Ui_UserManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGER_H
