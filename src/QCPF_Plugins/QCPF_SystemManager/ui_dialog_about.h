/********************************************************************************
** Form generated from reading UI file 'dialog_about.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ABOUT_H
#define UI_DIALOG_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_About
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *btnClose;

    void setupUi(QDialog *Dialog_About)
    {
        if (Dialog_About->objectName().isEmpty())
            Dialog_About->setObjectName(QString::fromUtf8("Dialog_About"));
        Dialog_About->resize(560, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../bin/debug/Images/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog_About->setWindowIcon(icon);
        label = new QLabel(Dialog_About);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 181, 41));
        label->setStyleSheet(QString::fromUtf8("font: 87 10pt \"Arial Black\";"));
        label_2 = new QLabel(Dialog_About);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(390, 230, 161, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 87 10pt \"Arial Black\";"));
        label_3 = new QLabel(Dialog_About);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(430, 20, 111, 31));
        label_3->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";"));
        label_4 = new QLabel(Dialog_About);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 70, 491, 171));
        label_4->setStyleSheet(QString::fromUtf8("font: 9pt \"Courier New\";"));
        label_4->setTextFormat(Qt::AutoText);
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_4->setWordWrap(true);
        btnClose = new QPushButton(Dialog_About);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(390, 260, 141, 31));
        label->raise();
        label_3->raise();
        label_4->raise();
        btnClose->raise();
        label_2->raise();

        retranslateUi(Dialog_About);

        QMetaObject::connectSlotsByName(Dialog_About);
    } // setupUi

    void retranslateUi(QDialog *Dialog_About)
    {
        Dialog_About->setWindowTitle(QCoreApplication::translate("Dialog_About", "About", nullptr));
        label->setText(QCoreApplication::translate("Dialog_About", "GPL . QCPFrame", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog_About", "Powered by Jamie.T", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog_About", "Version: v1.0.0.1", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog_About", "    QCPFrame is a plugin frame that base on Qt. it can help you and your team develop agilely. for QCPFrame family, any element of your program such as function, menu-bar item, tool-bar item, status-bar item, docks of workspace can be a plugin or widget, it can be loaded, unloaded, edited by the \"view editer\" who also is a plugin.  the \"Core\" of the QCPFrame can make you run a console with base plugin system, the \"View Model\" can run them with UI, it's a multi-layered plugin system that can run in Linxu and Windows. in the end, QCPFrame is a opensource project for you. any questions, please let me know, you can also submit your code, let's make it better together, thanks!", nullptr));
        btnClose->setText(QCoreApplication::translate("Dialog_About", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_About: public Ui_Dialog_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ABOUT_H
